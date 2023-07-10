#include "math/vec.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

vec vec_new(int n)
{
    vec res = (vec)malloc(n * sizeof(REAL) + sizeof(int));
    res = (vec)((int *)res + 1);
    vecn(res) = n;
    return res;
}

vec vec_free(vec v)
{
    v = (vec)((int *)v - 1);
    free(v);
    v = NULL;
}

vec vec_add(vec v1, vec v2)
{
    vec res = NULL;

    if(vecn(v1) == vecn(v2))
    {
        res = vec_new(vecn(v1));
        for(int i = 0; i < vecn(v1); i++)
        {
            res[i] = v1[i] + v2[i];
        }
    }
    return res;
}

vec vec_minus(vec v1, vec v2)
{
    vec res = NULL;

    if(vecn(v1) == vecn(v2))
    {
        res = vec_new(vecn(v1));
        for(int i = 0; i < vecn(v1); i++)
        {
            res[i] = v1[i] - v2[i];
        }
    }
    return res;
}

vec vec_multiply(vec v, double factor)
{
    vec res = vec_new(vecn(v));

    for(int i = 0; i < vecn(res); i++)
    {
        res[i] = v[i] * factor;
    }
    return res;
}

vec vec_divide(vec v, double factor)
{
    vec res = vec_new(vecn(v));

    if(factor != 0.0)
    {
        for(int i = 0; i < vecn(res); i++)
        {
            res[i] = v[i] / factor;
        }
    }

    return res;
}

REAL vec_dot(vec v1, vec v2)
{
    REAL res = 0.0;
    if(vecn(v1) == vecn(v2))
    {
        for(int i = 0; i < vecn(v1); i++)
        {
            res += v1[i] * v2[i];
        }
    }

    return res;
}

vec vec3_cross(vec v1, vec v2)
{
    vec res = NULL;

    if(vecn(v1) == 3 && vecn(v2) == 3)
    {
        res = vec_new(vecn(v1));

        res[0] = v1[1] * v2[2] - v1[2] * v2[1];
        res[1] = v1[2] * v2[0] - v1[0] * v2[2];
        res[2] = v1[0] * v2[1] - v1[1] * v2[0];
    }
    return res;
}

REAL vec_length_2(vec v)
{
    REAL res = 0.0;
    for(int i = 0; i < vecn(v); i++)
    {
        res += v[i] * v[i];
    }

    return res;
}

double vec_length(vec v)
{
    return sqrt(vec_length_2(v));
}

void vec_normalize(vec v)
{
    REAL len = vec_length(v);
    if(len != 0.0)
    {
        for(int i = 0; i < vecn(v); i++)
        {
            v[i] /= len;
        }
    }
}

double vec2_cross(vec v1, vec v2)
{
    if(vecn(v1) == 3 && vecn(v2) == 2)
    {
        return v1[0] * v2[1] - v1[1] * v2[0];
    }
    return 0.0;
}

void vec_set(vec v1, vec v2)
{
    if(vecn(v1) == vecn(v2))
    {
        memcpy_s(v1, vecsize(v1), v2, vecsize(v2));
    }
}
