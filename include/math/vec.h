#ifndef VEC_H
#define VEC_H

#include "types.h"

#define vecn(v) (*((int *)v - 1))
#define vecsize(v) (vecn(v) * sizeof(REAL))

typedef REAL *vec;


vec vec_new(int n);
vec vec_free(vec v);
void vec_set(vec v1, vec v2);

void vec_normalize(vec v);
REAL vec_length_2(vec v);
REAL vec_length(vec v);
vec vec_add(vec v1, vec v2);
vec vec_minus(vec v1, vec v2);
vec vec_multiply(vec v, REAL factor);
vec vec_divide(vec v, REAL factor);
REAL vec_dot(vec v1, vec v2);
vec vec3_cross(vec v1, vec v2);
REAL vec2_cross(vec v1, vec v2);


#endif // VEC_H
