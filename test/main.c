#include "math/mat.h"
#include <stdio.h>

int main()
{
    vec v1 = vec_new(3);
    vec v2 = vec_new(3);

    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    v2[0] = 14.0;
    v2[1] = 42.0;
    v2[2] = 32.09;

    vec v3 = vec_add(v1, v2);
    vec v4 = vec3_cross(v3, v2);
    vec_normalize(v3);

    for(int i = 0; i < vecn(v4); i++)
    {
        printf("%f ", v4[i]);
    }
    printf("\n");

    vec_free(v1);
    vec_free(v2);
    vec_free(v3);
    vec_free(v4);


    mat m1 = mat_new(4, 4);
    mat m2 = mat_new(4, 4);
    m1[3] = 23.09;
    mat m3 = mat_multiply_matrix(m1, m2);

    for(int i = 0; i < matrow(m3); i++)
    {
        for(int j = 0; j < matcolumn(m3); j++)
        {
            printf("%f ", m(m3, i, j));
        }
        printf("\n");
    }

    mat_free(m1);

    return 0;
}
