/* This file is part of punani-strike
 * Copyright (c) 2011 Gianni Tedesco
 * Released under the terms of GPLv3
*/
#ifndef _VEC_H
#define _VEC_H

#include <punani/punani.h>
#include <math.h>

#define X 0
#define Y 1
#define Z 2

static inline void v_zero(vec3_t v)
{
	unsigned int i;
	for(i = 0; i < 3; i++)
		v[i] = 0.0f;
}

static inline float v_len(const vec3_t v)
{
	float len;

	len = (v[X] * v[X]) +
		(v[Y] * v[Y]) +
		(v[Z] * v[Z]);

	return sqrt(len);
}

static inline float v_abslen(const vec3_t v)
{
	float len;

	len = (v[X] * v[X]) +
		(v[Y] * v[Y]) +
		(v[Z] * v[Z]);

	return fabs(sqrt(len));
}

static inline void  v_scale(vec3_t v, const float s)
{
	v[X] *= s;
	v[Y] *= s;
	v[Z] *= s;
}

static inline void v_normalize(vec3_t v)
{
	float len = v_len(v);

	if ( len == 0.0f )
		return;

	len = 1 / len;
	v[X] *= len;
	v[Y] *= len;
	v[Z] *= len;
}

static inline float v_normlen(vec3_t v)
{
	float inv, len = v_len(v);

	if ( len == 0.0f )
		return 0.0;

	inv = 1 / len;
	v[X] *= inv;
	v[Y] *= inv;
	v[Z] *= inv;
	return len;
}

static inline void v_add(vec3_t d, const vec3_t v1, const vec3_t v2)
{
	unsigned int i;
	for(i = 0; i < 3; i++)
		d[i] = v1[i] + v2[i];
}

static inline void v_sub(vec3_t d, const vec3_t v1, const vec3_t v2)
{
	unsigned int i;
	for(i = 0; i < 3; i++)
		d[i] = v1[i] - v2[i];
}

static inline void v_div(vec3_t d, const vec3_t v1, const vec3_t v2)
{
	unsigned int i;
	for(i = 0; i < 3; i++)
		d[i] = v1[i] / v2[i];
}

static inline void v_mult(vec3_t d, const vec3_t v1, const vec3_t v2)
{
	unsigned int i;
	for(i = 0; i < 3; i++)
		d[i] = v1[i] * v2[i];
}
static inline void v_cross_product(vec3_t d, const vec3_t v1, const vec3_t v2)
{
	d[X] = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
	d[Y] = (v1[Z] * v2[X]) - (v1[X] * v2[Z]);
	d[Z] = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
}

static inline float v_dot_product(const vec3_t v1, const vec3_t v2)
{
	return (v1[X] * v2[X] + v1[Y] * v2[Y] + v1[Z] * v2[Z]);
}

static inline void mat4_mult_point(vec3_t c, mat4_t m, vec3_t a)
{
	c[0] = m[0][0] * a[0] + m[1][0] * a[1] + m[2][0] * a[2] + m[3][0];
	c[1] = m[0][1] * a[0] + m[1][1] * a[1] + m[2][1] * a[2] + m[3][1];
	c[2] = m[0][2] * a[0] + m[1][2] * a[1] + m[2][2] * a[2] + m[3][2];
}

static inline void v_copy(vec3_t out, const vec3_t in)
{
	unsigned int i;
	for(i = 0; i < 3; i++)
		out[i] = in[i];
}

/* matrix and orthonormal basis functions */
void mat4_mult(mat4_t out, const mat4_t a, const mat4_t b);
void mat3_mult(mat3_t out, const mat3_t a, const mat3_t b);
void mat3_load_identity(mat3_t mat);
void mat4_load_identity(mat3_t mat);
void mat3_transpose(mat3_t mat); /* only transposes upper-left 3x3 */
void mat4_transpose(mat4_t mat);
void basis_rotateX(mat3_t mat, float angle);
void basis_rotateY(mat3_t mat, float angle);
void basis_rotateZ(mat3_t mat, float angle);
void basis_transform(const mat3_t mat, vec3_t out, const vec3_t in);

/* Oriented bounding boxes */
void obb_build_aabb(const struct obb *obb, vec3_t mins, vec3_t maxs);
void obb_from_aabb(struct obb *obb, const vec3_t mins, const vec3_t maxs);
int collide_obb(const struct obb *a, const struct obb *b);

/* collision detection: sweep */
int aabb_sweep(const struct AABB_Sweep *a, const struct AABB_Sweep *b,
		vec2_t u);

/* collision detection: prune */
int collide_box_line(const vec3_t mins, const vec3_t maxs,
			const vec3_t a, const vec3_t b, vec3_t hit);

#endif /* _VEC_H */
