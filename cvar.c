#include <punani/punani.h>
#include <punani/cvar.h>
#include <punani/console.h>
#include "list.h"

#define CVAR_TYPE_UNDEFINED      0
#define CVAR_TYPE_FLOAT          1
#define CVAR_TYPE_UNSIGNED_INT   2

struct _cvar_ns {
	struct list_head ns_list;

	const char *ns_name;
	struct list_head c_list;
};

struct _cvar {
	struct list_head c_list;
	
	int c_type;
	int c_flags;
	
	union {
		float *f;
		unsigned int *ui;
	} c_ptr;
	
	union {
		float f;
		unsigned int ui;
	} c_default_val;
	
	char *c_name;
};


static LIST_HEAD(cvar_ns_list);


cvar_ns_t cvar_ns_new(const char *ns)
{
	cvar_ns_t res = calloc(1, sizeof(*res));
	res->ns_name = ns;
	INIT_LIST_HEAD(&res->c_list);
	list_add_tail(&res->ns_list, &cvar_ns_list);
	return res;
}

void cvar_ns_free(cvar_ns_t ns)
{
	cvar_t c, t;
	list_for_each_entry_safe(c, t, &ns->c_list, c_list) {
		list_del(&c->c_list);
		free(c);
	}
	list_del(&ns->ns_list);
	free(ns);
}

cvar_ns_t cvar_get_ns(const char *ns)
{
	cvar_ns_t c;
	list_for_each_entry(c, &cvar_ns_list, ns_list) {
		if ( !strcmp(c->ns_name, ns) ) {
			return c;
		}
	}

	return NULL;
}

cvar_t cvar_locate(cvar_ns_t ns, const char *name)
{
	cvar_t c;

	list_for_each_entry(c, &ns->c_list, c_list) {
		if ( !strcmp(c->c_name, name)) {
			return c;
		}
	}
	
	return NULL;
}

void cvar_register_float(cvar_ns_t ns, const char *name, int flags, float *ptr)
{
	/* see if it already exists first. */
	cvar_t c;
	
	c = cvar_locate(ns, name);
	
	if ( NULL != c ) {
		con_printf("cvar already registered: %s.%s\n", ns->ns_name, name);
		return;
	}

	c = (cvar_t) calloc(1, sizeof(*c));
	
	c->c_name = strdup(name);
	c->c_type = CVAR_TYPE_FLOAT;
	c->c_ptr.f = ptr;
	c->c_default_val.f = *ptr;
	c->c_flags = flags;
	
	list_add_tail(&c->c_list, &ns->c_list);
}

void cvar_register_uint(cvar_ns_t ns, const char *name, int flags, unsigned int *ptr)
{
	/* see if it already exists first. */
	cvar_t c;
	
	c = cvar_locate(ns, name);
	
	if ( NULL != c ) {
		con_printf("cvar already registered: %s.%s\n", ns->ns_name, name);
		return;
	}

	c = (cvar_t) calloc(1, sizeof(*c));
	
	c->c_name = strdup(name);
	c->c_type = CVAR_TYPE_UNSIGNED_INT;
	c->c_ptr.ui = ptr;
	c->c_default_val.ui = *ptr;
	c->c_flags = flags;
	
	list_add_tail(&c->c_list, &ns->c_list);
}

static int parse_float(const char *str, float *val)
{
	char *end;

	float newval = strtod(str, &end);
	if ( end == str || (*end != '\0' && *end != 'f') )
		return 0;
		
	*val = newval;

	return 1;
}

static int parse_uint(const char *str, unsigned int *val)
{
	char *end;

	unsigned int newval = strtol(str, &end, 10);
	if ( end == str || (*end != '\0' && *end != 'f') )
		return 0;
		
	*val = newval;

	return 1;
}

/* Easy string tokeniser */
static int easy_explode(char *str, char split,
			char **toks, int max_toks)
{
	char *tmp;
	int tok;
	int state;

	for(tmp=str,state=tok=0; *tmp && tok <= max_toks; tmp++) {
		if ( state == 0 ) {
			if ( *tmp == split && (tok < max_toks)) {
				toks[tok++] = NULL;
			}else if ( !isspace(*tmp) ) {
				state = 1;
				toks[tok++] = tmp;
			}
		}else if ( state == 1 ) {
			if ( tok < max_toks ) {
				if ( *tmp == split || isspace(*tmp) ) {
					*tmp = '\0';
					state = 0;
				}
			}else if ( *tmp == '\n' )
				*tmp = '\0';
		}
	}

	return tok;
}


void cvar_con_input(char *input)
{
	char *tok[2];
	int ntok;

	/* expect <name> <val> */
	ntok = easy_explode(input, ' ', tok, 2);
	if ( ntok != 2 ) {
		con_printf("bad variable: should be <obj>.<name> <val>\n");
		return;
	}
		
	/* expect <ns>.<name> */
	char *var_name[2];
	ntok = easy_explode(tok[0], '.', var_name, 2);
	
	if (ntok != 2) {
		con_printf("bad variable: should be <obj>.<name> <val>\n");
		return;
	}
	
	/* see if we've got a matching cvar */
	cvar_ns_t ns;
	cvar_t cvar = NULL;

	ns = cvar_get_ns(var_name[0]);
	if ( NULL != ns ) {
		cvar = cvar_locate(ns, var_name[1]);
	}
	
	if ( NULL == cvar ) {
		con_printf("unknown variable: %s.%s\n", var_name[0], var_name[1]);
		return;
	}
	
	cvar_set(ns, cvar, tok[1]);
}

void cvar_set(cvar_ns_t ns, cvar_t cvar, const char *value)
{
	if ( NULL == cvar ) {
		con_printf("cvar_set with NULL: value '%s' ignored\n", value);
		return;
	}
	
	switch(cvar->c_type) {
	case CVAR_TYPE_UNDEFINED:
		con_printf("cvar_set: CVAR_TYPE_UNDEFINED passed. %s.%s\n", ns->ns_name, cvar->c_name);
		break;
	case CVAR_TYPE_FLOAT:
		if (!parse_float(value, cvar->c_ptr.f)) {
			con_printf("%s.%s: bad float %s\n", ns->ns_name, cvar->c_name, value);
		}
		break;
	case CVAR_TYPE_UNSIGNED_INT:
		if (!parse_uint(value, cvar->c_ptr.ui)) {
			con_printf("%s.%s: bad uint %s\n", ns->ns_name, cvar->c_name, value);
		}
		break;
	}
}

void cvar_ns_load(cvar_ns_t ns)
{
	int const buf_size = 256;
	FILE *fin;
	char buf[buf_size];
	char con_input[buf_size];
	char *ptr, *end;
	unsigned int line;
	
	snprintf(buf, buf_size, "%s.cfg", ns->ns_name);

	fin = fopen(buf, "rt");
	if (!fin) {
		con_printf("cvar_load: unable to open %s for reading\n", buf);
		return;
	}
	
	for(line = 1; fgets(buf, sizeof(buf), fin); line++ ) {

		end = strchr(buf, '\r');
		if ( NULL == end )
			end = strchr(buf, '\n');

		if ( NULL == end ) {
			con_printf("cvar_load: %s:%u: Line too long\n", buf, line);
			goto out_free;
		}
		
		/* strip trailing whitespace */
		for(end = end - 1; isspace(*end); end--)
			*end= '\0';
		/* strip leading whitespace */
		for(ptr = buf; isspace(*ptr); ptr++)
			/* nothing */;

		if ( *ptr == '\0' || *ptr == '#' )
			continue;

		snprintf(con_input, buf_size, "%s.%s", ns->ns_name, ptr);

		cvar_con_input(ptr);
	}
	
out_free:
	fclose(fin);

}

void cvar_ns_save(cvar_ns_t ns)
{
	int const buf_size = 256;
	char filename[buf_size];
	cvar_t c;
	FILE *out;
	
	snprintf(filename, buf_size, "%s.cfg", ns->ns_name);


	out = fopen(filename, "wt");
	if (!out) {
		con_printf("cvar_save_all: unable to open %s for writing\n", filename);
		return;
	}
	
	fprintf(out, "# %s written by cvar_save_all\n", ns->ns_name);
	
	list_for_each_entry(c, &ns->c_list, c_list) {
		if (~c->c_flags & CVAR_FLAG_SAVE_NEVER) {
			switch(c->c_type) {
			case CVAR_TYPE_UNDEFINED:
				con_printf("cvar_save_all: CVAR_TYPE_UNDEFINED in save\n");
				break;
			case CVAR_TYPE_FLOAT:
				if (c->c_flags & CVAR_FLAG_SAVE_ALWAYS || *c->c_ptr.f != c->c_default_val.f) {
					fprintf(out, "%s.%s %f\n", ns->ns_name, c->c_name, *c->c_ptr.f);
				}
				break;
			case CVAR_TYPE_UNSIGNED_INT:
				if (c->c_flags & CVAR_FLAG_SAVE_ALWAYS || *c->c_ptr.ui != c->c_default_val.ui) {
					fprintf(out, "%s.%s %d\n", ns->ns_name, c->c_name, *c->c_ptr.ui);
				}
				break;
			}
		}
	}
	
	fclose(out);
}
