/* This file is part of punani-strike
 * Copyright (c) 2012 Gianni Tedesco
 * Released under the terms of GPLv3
*/
#include <punani/punani.h>
#include <punani/vec.h>

static int intersect(float fDst1, float fDst2,
			   const vec3_t a, const vec3_t b, vec3_t hit)
{
	if ((fDst1 * fDst2) >= 0.0f)
		return 0;
	if (fDst1 == fDst2)
		return 0;

	//v_sub(hit, b, a);
	//v_add(hit, a);
	v_copy(hit, b);
	v_scale(hit, (-fDst1 / (fDst2 - fDst1)));
	return 1;
}

static int in_box(vec3_t hit, const vec3_t mins, const vec3_t maxs,
		 const int Axis)
{
	if (Axis == 1 && hit[2] > mins[2] && hit[2] < maxs[2]
	    && hit[1] > mins[1]
	    && hit[1] < maxs[1])
		return 1;
	if (Axis == 2 && hit[2] > mins[2] && hit[2] < maxs[2]
	    && hit[0] > mins[0]
	    && hit[0] < maxs[0])
		return 1;
	if (Axis == 3 && hit[0] > mins[0] && hit[0] < maxs[0]
	    && hit[1] > mins[1]
	    && hit[1] < maxs[1])
		return 1;
	return 0;
}

int collide_box_line(const vec3_t mins, const vec3_t maxs,
			const vec3_t a, const vec3_t b, vec3_t hit)
{
	/* fast checks, both ends of line on same side of 6 planes */
	if (b[0] < mins[0] && a[0] < mins[0])
		return 0;
	if (b[0] > maxs[0] && a[0] > maxs[0])
		return 0;
	if (b[1] < mins[1] && a[1] < mins[1])
		return 0;
	if (b[1] > maxs[1] && a[1] > maxs[1])
		return 0;
	if (b[2] < mins[2] && a[2] < mins[2])
		return 0;
	if (b[2] > maxs[2] && a[2] > maxs[2])
		return 0;

	/* start inside box */
	if (a[0] > mins[0] && a[0] < maxs[0] &&
	    a[1] > mins[1] && a[1] < maxs[1] &&
	    a[2] > mins[2] && a[2] < maxs[2]) {
		v_copy(hit, a);
		return 1;
	}

	if ((intersect(a[0] - mins[0], b[0] - mins[0], a, b, hit)
	     && in_box(hit, mins, maxs, 1))
	    || (intersect(a[1] - mins[1], b[1] - mins[1], a, b, hit)
		&& in_box(hit, mins, maxs, 2))
	    || (intersect(a[2] - mins[2], b[2] - mins[2], a, b, hit)
		&& in_box(hit, mins, maxs, 3))
	    || (intersect(a[0] - maxs[0], b[0] - maxs[0], a, b, hit)
		&& in_box(hit, mins, maxs, 1))
	    || (intersect(a[1] - maxs[1], b[1] - maxs[1], a, b, hit)
		&& in_box(hit, mins, maxs, 2))
	    || (intersect(a[2] - maxs[2], b[2] - maxs[2], a, b, hit)
		&& in_box(hit, mins, maxs, 3)))
		return 1;

	return 0;
}

#define A(row,col)  (a[row][col])
#define B(row,col)  (b[row][col])
#define P(row,col)  (out[row][col])

/**
 * Perform a full 4x4 matrix multiplication.
 *
 * \param a matrix.
 * \param b matrix.
 * \param product will receive the product of \p a and \p b.
 *
 * \warning Is assumed that \p product != \p b. \p product == \p a is allowed.
 *
 * \note KW: 4*16 = 64 multiplications
 *
 * \author This \c matmul was contributed by Thomas Malik
 */
void mat4_mult(mat4_t out, const mat4_t a, const mat4_t b)
{
   int i;
   for (i = 0; i < 4; i++) {
      const float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }
}

/**
 * Multiply two matrices known to occupy only the top three rows, such
 * as typical model matrices, and orthogonal matrices.
 *
 * \param a matrix.
 * \param b matrix.
 * \param product will receive the product of \p a and \p b.
 */
void mat3_mult(mat3_t out, const mat3_t a, const mat3_t b)
{
   int i;
   for (i = 0; i < 3; i++) {
      const float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2);
   }
}

#undef A
#undef B
#undef P

void mat3_load_identity(mat3_t mat)
{
	unsigned int i, j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if ( i == j ) {
				mat[i][j] = 1.0;
			}else{
				mat[i][j] = 0.0;
			}
		}
	}
}

void mat4_load_identity(mat3_t mat)
{
	unsigned int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if ( i == j ) {
				mat[i][j] = 1.0;
			}else{
				mat[i][j] = 0.0;
			}
		}
	}
}

static void swap4(mat4_t mat, unsigned x, unsigned y)
{
	float tmp;
	tmp = mat[x][y];
	mat[x][y] = mat[y][x];
	mat[y][x] = tmp;
}

void mat4_transpose(mat4_t mat)
{
	swap4(mat, 0, 1);
	swap4(mat, 0, 2);
	swap4(mat, 1, 2);
}

static void swap3(mat3_t mat, unsigned x, unsigned y)
{
	float tmp;
	tmp = mat[x][y];
	mat[x][y] = mat[y][x];
	mat[y][x] = tmp;
}

void mat3_transpose(mat3_t mat)
{
	swap3(mat, 0, 1);
	swap3(mat, 0, 2);
	swap3(mat, 1, 2);
}

/* Othonormal basis rotation */
void basis_rotateX(mat3_t mat, float angle)
{
	float s, c;
	mat3_t m;

	if ( angle == 0.0 )
		return;

	mat3_load_identity(m);
	s = sin(angle);
	c = cos(angle);

	m[1][1] = c;
	m[2][2] = c;
	m[1][2] = -s;
	m[2][1] = s;

	mat3_mult(mat, (const float (*)[3])mat, (const float (*)[3])m);
}

void basis_rotateY(mat3_t mat, float angle)
{
	float s, c;
	mat3_t m;

	if ( angle == 0.0 )
		return;

	mat3_load_identity(m);
	s = sin(angle);
	c = cos(angle);

	m[0][0] = c;
	m[2][2] = c;
	m[0][2] = -s;
	m[2][0] = s;

	mat3_mult(mat, (const float (*)[3])mat, (const float (*)[3])m);
}

void basis_rotateZ(mat3_t mat, float angle)
{
	float s, c;
	mat3_t m;

	if ( angle == 0.0 )
		return;

	mat3_load_identity(m);
	s = sin(angle);
	c = cos(angle);

	m[0][0] = c;
	m[1][1] = c;
	m[0][1] = -s;
	m[1][0] = s;

	mat3_mult(mat, (const float (*)[3])mat, (const float (*)[3])m);
}

int collide_obb(const struct obb *a, const struct obb *b)
{
	vec3_t v, T;
	mat3_t R, Rabs;
	float ra, rb, t;
	unsigned i, k;

	/* compute displacement between 2 centres */
	v_sub(v, b->origin, a->origin);

	/* get column vectors for A's rotation */
	memcpy(R, a->rot, sizeof(R));
	mat3_transpose(R);

	/* translate displacement in to A's frame */
#if 0
	T[0] = v_dot_product(v, R[0]);
	T[1] = v_dot_product(v, R[1]);
	T[2] = v_dot_product(v, R[2]);
#else
	T[0] = v_dot_product(v, a->rot[0]);
	T[1] = v_dot_product(v, a->rot[1]);
	T[2] = v_dot_product(v, a->rot[2]);
#endif

	/* tanspose multiply of A and B's rotation computes
	 * rotation in to A's coordinate space. Centre of A
	 * is then treated as zero vector.
	*/
#if 0
	mat3_mult(R, (const float (*)[3]) R, (const float (*)[3])b->rot);
#else
	for (i = 0; i < 3; i++) {
		for (k = 0; k < 3; k++) {
			R[i][k] = v_dot_product(a->rot[i], b->rot[k]);
		}
	}
	// memcpy(R, b->rot, sizeof(R)); // since A is not rotated
#endif

	/* ALGORITHM: Use the separating axis test for all 15 potential
	 * separating axes. If a separating axis could not be found, the
	 * twoboxes overlap.
	*/

#if 1
	/* a's basis vectors */
	for (i = 0; i < 3; i++) {
		ra = a->dim[i];
		rb = b->dim[0] * fabs(R[i][0]) + b->dim[1] * fabs(R[i][1]) +
		    b->dim[2] * fabs(R[i][2]);
		t = fabs(T[i]);
		if (t > ra + rb)
			return 0;
	}

	/* b's basis vectors */
	for (k = 0; k < 3; k++) {
		ra = a->dim[0] * fabs(R[0][k]) + a->dim[1] * fabs(R[1][k]) +
		    a->dim[2] * fabs(R[2][k]);
		rb = b->dim[k];
		t = fabs(T[0] * R[0][k] + T[1] * R[1][k] + T[2] * R[2][k]);
		if (t > ra + rb)
			return 0;
	}

	/* 9 cross products */

	/* L = A0 x B0 */
	ra = a->dim[1] * fabs(R[2][0]) + a->dim[2] * fabs(R[1][0]);
	rb = b->dim[1] * fabs(R[0][2]) + b->dim[2] * fabs(R[0][1]);
	t = fabs(T[2] * R[1][0] - T[1] * R[2][0]);
	if (t > ra + rb)
		return 0;

	/* L = A0 x B1 */
	ra = a->dim[1] * fabs(R[2][1]) + a->dim[2] * fabs(R[1][1]);
	rb = b->dim[0] * fabs(R[0][2]) + b->dim[2] * fabs(R[0][0]);
	t = fabs(T[2] * R[1][1] - T[1] * R[2][1]);
	if (t > ra + rb)
		return 0;

	/* L = A0 x B2 */
	ra = a->dim[1] * fabs(R[2][2]) + a->dim[2] * fabs(R[1][2]);
	rb = b->dim[0] * fabs(R[0][1]) + b->dim[1] * fabs(R[0][0]);
	t = fabs(T[2] * R[1][2] - T[1] * R[2][2]);
	if (t > ra + rb)
		return 0;

	/* L = A1 x B0 */
	ra = a->dim[0] * fabs(R[2][0]) + a->dim[2] * fabs(R[0][0]);
	rb = b->dim[1] * fabs(R[1][2]) + b->dim[2] * fabs(R[1][1]);
	t = fabs(T[0] * R[2][0] - T[2] * R[0][0]);
	if (t > ra + rb)
		return 0;

	/* L = A1 x B1 */
	ra = a->dim[0] * fabs(R[2][1]) + a->dim[2] * fabs(R[0][1]);
	rb = b->dim[0] * fabs(R[1][2]) + b->dim[2] * fabs(R[1][0]);
	t = fabs(T[0] * R[2][1] - T[2] * R[0][1]);
	if (t > ra + rb)
		return 0;

	/* L = A1 x B2 */
	ra = a->dim[0] * fabs(R[2][2]) + a->dim[2] * fabs(R[0][2]);
	rb = b->dim[0] * fabs(R[1][1]) + b->dim[1] * fabs(R[1][0]);
	t = fabs(T[0] * R[2][2] - T[2] * R[0][2]);
	if (t > ra + rb)
		return 0;

	/* L = A2 x B0 */
	ra = a->dim[0] * fabs(R[1][0]) + a->dim[1] * fabs(R[0][0]);
	rb = b->dim[1] * fabs(R[2][2]) + b->dim[2] * fabs(R[2][1]);
	t = fabs(T[1] * R[0][0] - T[0] * R[1][0]);
	if (t > ra + rb)
		return 0;

	/* L = A2 x B1 */
	ra = a->dim[0] * fabs(R[1][1]) + a->dim[1] * fabs(R[0][1]);
	rb = b->dim[0] * fabs(R[2][2]) + b->dim[2] * fabs(R[2][0]);
	t = fabs(T[1] * R[0][1] - T[0] * R[1][1]);
	if (t > ra + rb)
		return 0;

	/* L = A2 x B2 */
	ra = a->dim[0] * fabs(R[1][2]) + a->dim[1] * fabs(R[0][2]);
	rb = b->dim[0] * fabs(R[2][1]) + b->dim[1] * fabs(R[2][0]);
	t = fabs(T[1] * R[0][2] - T[0] * R[1][2]);
	if (t > ra + rb)
		return 0;
#else
	for(i = 0; i < 3; i++) {
		for(k = 0; k < 3; k++) {
			Rabs[i][k] = fabs(R[i][k]) + 0.0000000001;
		}
	}

	// test axes L = A0, L = A1, L = A2
	for (i = 0; i < 3; i++) {
		ra = a->dim[i];
		rb = b->dim[0] * Rabs[i][0] + b->dim[1] * Rabs[i][1] +
		    b->dim[2] * Rabs[i][2];
		if (fabs(T[i]) > ra + rb)
			return 0;
	}

	// test axes L = B0, L = B1, L = B2
	for (i = 0; i < 3; i++) {
		vec3_t R_col;
		ra = a->dim[0] * Rabs[0][i] + a->dim[1] * Rabs[1][i] +
		    a->dim[2] * Rabs[2][i];
		rb = b->dim[i];
		R_col[0] = R[0][i];
		R_col[1] = R[1][i];
		R_col[2] = R[2][i];
		if (fabs(v_dot_product(T, R_col)) > ra + rb)
			return 0;
	}

	// test axis L = A0 x B0
	ra = a->dim[1] * Rabs[Z][X] + a->dim[2] * Rabs[Y][X];
	rb = b->dim[1] * Rabs[X][Z] + b->dim[2] * Rabs[X][Y];
	if (fabs(T[Z] * R[Y][X] - T[Y] * R[Z][X]) > ra + rb)
		return 0;

	// test axis L = A0 x B1
	ra = a->dim[1] * Rabs[Z][Y] + a->dim[2] * Rabs[Y][Y];
	rb = b->dim[0] * Rabs[X][Z] + b->dim[2] * Rabs[X][X];
	if (fabs(T[Z] * R[Y][Y] - T[Y] * R[Z][Y]) > ra + rb)
		return 0;

	// test axis L = A0 x B2
	ra = a->dim[1] * Rabs[Z][Z] + a->dim[2] * Rabs[Y][Z];
	rb = b->dim[0] * Rabs[X][Y] + b->dim[1] * Rabs[X][X];
	if (fabs(T[Z] * R[Y][Z] - T[Y] * R[Z][Z]) > ra + rb)
		return 0;

	// test axis L = A1 x B0
	ra = a->dim[0] * Rabs[Z][X] + a->dim[2] * Rabs[X][X];
	rb = b->dim[1] * Rabs[Y][Z] + b->dim[2] * Rabs[Y][Y];
	if (fabs(T[X] * R[Z][X] - T[Z] * R[X][X]) > ra + rb)
		return 0;

	// test axis L = A1 x B1
	ra = a->dim[0] * Rabs[Z][Y] + a->dim[2] * Rabs[X][Y];
	rb = b->dim[0] * Rabs[Y][Z] + b->dim[2] * Rabs[Y][X];
	if (fabs(T[X] * R[Z][Y] - T[Z] * R[X][Y]) > ra + rb)
		return 0;

	// test axis L = A1 x B2
	ra = a->dim[0] * Rabs[Z][Z] + a->dim[2] * Rabs[X][Z];
	rb = b->dim[0] * Rabs[Y][Y] + b->dim[1] * Rabs[Y][X];
	if (fabs(T[X] * R[Z][Z] - T[Z] * R[X][Z]) > ra + rb)
		return 0;

	// test axis L = A2 x B0
	ra = a->dim[0] * Rabs[Y][X] + a->dim[1] * Rabs[X][X];
	rb = b->dim[1] * Rabs[Z][Z] + b->dim[2] * Rabs[Z][Y];
	if (fabs(T[Y] * R[X][X] - T[X] * R[Y][X]) > ra + rb)
		return 0;

	// test axis L = A2 x B1
	ra = a->dim[0] * Rabs[Y][Y] + a->dim[1] * Rabs[X][Y];
	rb = b->dim[0] * Rabs[Z][Z] + b->dim[2] * Rabs[Z][X];
	if (fabs(T[Y] * R[X][Y] - T[X] * R[Y][Y]) > ra + rb)
		return 0;

	// test axis L = A2 x B2
	ra = a->dim[0] * Rabs[Y][Z] + a->dim[1] * Rabs[X][Z];
	rb = b->dim[0] * Rabs[Z][Y] + b->dim[1] * Rabs[Z][X];
	if (fabs(T[Y] * R[X][Z] - T[X] * R[Y][Z]) > ra + rb)
		return 0;
#endif
	/* no separating axis found, threfore the two boxes overlap */
#if 0
	printf("\n");
	printf("A = %f,%f,%f %f,%f,%f\n",
		a->origin[0], a->origin[1], a->origin[2],
		a->dim[0], a->dim[1], a->dim[2]);
	printf("B = %f,%f,%f %f,%f,%f\n",
		b->origin[0], b->origin[1], b->origin[2],
		b->dim[0], b->dim[1], b->dim[2]);
	for(i = 0; i < 3; i++)
		printf("%f %f %f\n", R[i][0], R[i][1], R[i][2]);
	printf("T = %f %f %f\n", T[0], T[1], T[2]);
	printf("v = %f %f %f\n", v[0], v[1], v[2]);
#endif
	return 1;
}

void basis_transform(const mat3_t mat, vec3_t out, const vec3_t in)
{
	vec3_t tmp;

	v_copy(tmp, mat[0]);
	v_scale(tmp, in[0]);
	v_copy(out, tmp);

	v_copy(tmp, mat[1]);
	v_scale(tmp, in[1]);
	v_add(out, out, tmp);

	v_copy(tmp, mat[2]);
	v_scale(tmp, in[2]);
	v_add(out, out, tmp);
}

void obb_build_aabb(const struct obb *obb, vec3_t mins, vec3_t maxs)
{
	unsigned int i;

	v_copy(mins, obb->origin);
	v_copy(maxs, obb->origin);

	for(i = 0; i < 8; i++) {
		unsigned int j;
		vec3_t vec, tmp;

		if ( i & 1 )
			tmp[0] = obb->dim[0];
		else
			tmp[0] = obb->dim[0];
		if ( i & 2 )
			tmp[1] = obb->dim[1];
		else
			tmp[1] = obb->dim[1];
		if ( i & 4 )
			tmp[2] = obb->dim[2];
		else
			tmp[2] = obb->dim[2];

		basis_transform((const float (*)[3])obb->rot, vec, tmp);
		for(j = 0; j < 3; j++) {
			mins[j] = f_min(mins[j], vec[j]);
			maxs[j] = f_max(maxs[j], vec[j]);
		}
	}
	v_add(mins, mins, obb->origin);
	v_add(maxs, maxs, obb->origin);
}

void obb_from_aabb(struct obb *obb, const vec3_t mins, const vec3_t maxs)
{
	v_sub(obb->dim, maxs, mins);
	v_scale(obb->dim, 0.5);
	v_copy(obb->origin, obb->dim);
	v_add(obb->origin, obb->origin, mins);
	mat3_load_identity(obb->rot);
}

int aabb_sweep(const struct AABB_Sweep *a,
		const struct AABB_Sweep *b, vec2_t u)
{
	unsigned int i;
	vec3_t va, vb, v;
	vec3_t u_0 = {0, 0, 0};
	vec3_t u_1 = {2, 1, 1};

	/* the problem is solved in A's frame of reference */
	v_sub(va, a->b, a->a);
	v_sub(vb, b->b, b->a);

	/* relative velocity (in normalized time) */
	v_sub(v, vb, va);

	if ( v_len(v) == 0 )
		return 0;

#if 0
	printf("%f %f %f :: %f %f %f\n",
		a->mins[0], a->mins[1], a->mins[2],
		a->maxs[0], a->maxs[1], a->maxs[2]);
	printf("%f %f %f :: %f %f %f\n",
		b->mins[0], b->mins[1], b->mins[2],
		b->maxs[0], b->maxs[1], b->maxs[2]);
	printf("vel %f %f %f\n", v[0], v[1], v[2]);
	printf("times %f %f\n", u[0], u[1]);
#endif
	/* find the possible first and last times
	 * of overlap along each axis
	*/
	for (i = 0; i < 3; i++) {
		if (a->maxs[i] < b->mins[i] && v[i] < 0) {
			u_0[i] = (a->maxs[i] - b->mins[i]) / v[i];
		}else if (b->maxs[i] < a->mins[i] && v[i] > 0) {
			u_0[i] = (a->mins[i] - b->maxs[i]) / v[i];
		}

		if ( v[i] >= 0 && ((a->maxs[i] + v[i] < b->mins[i]) ||
					(a->mins[i] > b->maxs[i]))) {
			return 0;
		}else if ( v[i] < 0 && ((a->maxs[i] < b->mins[i]) ||
					(a->mins[i] + v[0] > b->maxs[i]))) {
			return 0;
		}

		if (b->maxs[i] > a->mins[i] && v[i] < 0.0) {
			u_1[i] = (a->mins[i] - b->maxs[i]) / v[i];
		}else if (a->maxs[i] > b->mins[i] && v[i] > 0) {
			u_1[i] = (a->maxs[i] - b->mins[i]) / v[i];
		}

	}

	/* possible first time of overlap */
	u[0] = f_max(u_0[0], f_max(u_0[1], u_0[2]));

	/* possible last time of overlap */
	u[1] = f_min(u_1[0], f_min(u_1[1], u_1[2]));

	/* they could have only collided if
	 * the first time of overlap occurred
	 * before the last time of overlap
	*/
	return (u[0] <= u[1]);
}
