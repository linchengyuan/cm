#ifndef MAT_H
#define MAT_H

#include "math/vec.h"

#define m(mat, row, column) (mat[matrow(mat) * column + row])
#define matrow(mat) (*((int *)mat - 2))
#define matcolumn(mat) (*((int *)mat - 1))
#define matsize(mat) (matrow(mat) * matcolumn(mat) * sizeof(REAL))


typedef REAL *mat;


mat mat_new(int row, int column);
void mat_free(mat m);
void mat_set(mat m1, mat m2);

void mat_transform(mat m, mat t);

void mat_identity(mat m);
mat mat_multiply_matrix(mat m1, mat m2);
vec mat_multiply_vec(mat m, vec v);


void mat4_inverse(mat m);
void mat4_reflect(mat m, vec normal);
void mat4_translate(mat m, vec v);
void mat4_rotate(mat m, vec axis, REAL angle);
void mat4_scale(mat m, vec v);

mat mat4_inverse_matrix(mat m);
mat mat4_reflect_matrix(mat m, vec normal);
mat mat4_translate_matrix(vec v);
mat mat4_rotate_matrix(vec axis, REAL angle);
mat mat4_scale_matrix(vec v);


#endif // MAT_H
