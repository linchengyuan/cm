#include "math/mat.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

mat mat_new(int row, int column)
{
    mat res = (mat)malloc(row * column * sizeof(REAL) + 2 * sizeof(int));
    res = (mat)((int *)res + 2);

    matrow(res) = row;
    matcolumn(res) = column;

    mat_identity(res);

    return res;
}

void mat_free(mat m)
{
    m = (mat)((int *)m - 2);
    free(m);
    m = NULL;
}

void mat_set(mat m1, mat m2)
{
    if(matrow(m1) == matrow(m2) && matcolumn(m1) == matcolumn(m2))
    {
        memcpy_s(m1, matsize(m1), m2, matsize(m2));
    }
}

void mat_transform(mat m, mat t)
{
    mat tmp = mat_multiply_matrix(t, m);
    if(tmp != NULL)
    {
        mat_set(m, tmp);
        mat_free(tmp);
    }
}




void mat_identity(mat m)
{
    for(int r = 0; r < matrow(m); r++)
    {
        for(int c = 0; c < matcolumn(m); c++)
        {
            if(r == c)
            {
                m(m, r, c) = 1.0;
            }
            else
            {
                m(m, r, c) = 0.0;
            }
        }
    }
}

mat mat_multiply_matrix(mat m1, mat m2)
{
    mat res = NULL;
    if(matcolumn(m1) == matrow(m2) && matrow(m1) == matcolumn(m2))
    {
        res = mat_new(matrow(m1), matcolumn(m2));

        for(int r = 0; r < matrow(m1); r++)
        {
            for(int c = 0; c < matcolumn(m2); c++)
            {
                m(res, r, c) = 0.0;
                for(int i = 0; i < matcolumn(m1); i++)
                {
                    m(res, r, c) += m(m1, r, i) * m(m2, i, c);
                }
            }
        }
    }
    return res;
}

vec mat_multiply_vec(mat m, vec v)
{
    vec res = vec_new(vecn(v));

    for(int i = 0; i < vecn(v); i++)
    {
        for(int j = 0; j < vecn(v); j++)
        {
            res[i] += m(m, i, j) * v[j];
        }
    }
    return res;
}

mat mat4_inverse_matrix(mat m)
{
    if(matrow(m) != 4 || matcolumn(m) != 4)
    {
        return NULL;
    }

    mat res = mat_new(matrow(m), matcolumn(m));
    REAL s[6], c[6];

    s[0] = m[0] * m[5] - m[4] * m[1];
    s[1] = m[0] * m[6] - m[4] * m[2];
    s[2] = m[0] * m[7] - m[4] * m[3];
    s[3] = m[1] * m[6] - m[5] * m[2];
    s[4] = m[1] * m[7] - m[5] * m[3];
    s[5] = m[2] * m[7] - m[6] * m[3];

    c[0] = m[8] * m[13] - m[12] * m[9];
    c[1] = m[8] * m[14] - m[12] * m[10];
    c[2] = m[8] * m[15] - m[12] * m[11];
    c[3] = m[9] * m[14] - m[13] * m[10];
    c[4] = m[9] * m[15] - m[13] * m[11];
    c[5] = m[10] * m[15] - m[14] * m[11];




    //Assumes it Is invertible
    REAL idet;
    idet = 1.0 / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

    res[0] = (m[5] * c[5] - m[6] * c[4] + m[7] * c[3]) * idet;
    res[1] = (-m[1] * c[5] + m[2] * c[4] - m[3] * c[3]) * idet;
    res[2] = (m[13] * s[5] - m[14] * s[4] + m[15] * s[3]) * idet;
    res[3] = (-m[9] * s[5] + m[10] * s[4] - m[11] * s[3]) * idet;

    res[4] = (-m[4] * c[5] + m[6] * c[2] - m[7] * c[1]) * idet;
    res[5] = (m[0] * c[5] - m[2] * c[2] + m[3] * c[1]) * idet;
    res[6] = (-m[12] * s[5] + m[14] * s[2] - m[15] * s[1]) * idet;
    res[7] = (m[8] * s[5] - m[10] * s[2] + m[11] * s[1]) * idet;

    res[8] = (m[4] * c[4] - m[5] * c[2] + m[7] * c[0]) * idet;
    res[9] = (-m[0] * c[4] + m[1] * c[2] - m[3] * c[0]) * idet;
    res[10] = (m[12] * s[4] - m[13] * s[2] + m[15] * s[0]) * idet;
    res[11] = (-m[8] * s[4] + m[9] * s[2] - m[11] * s[0]) * idet;

    res[12] = (-m[4] * c[3] + m[5] * c[1] - m[6] * c[0]) * idet;
    res[13] = (m[0] * c[3] - m[1] * c[1] + m[2] * c[0]) * idet;
    res[14] = (-m[12] * s[3] + m[13] * s[1] - m[14] * s[0]) * idet;
    res[15] = (m[8] * s[3] - m[9] * s[1] + m[10] * s[0]) * idet;

    return res;
}

mat mat4_reflect_matrix(mat m, vec normal)
{
    if(matrow(m) != 4 || matcolumn(m) != 4)
    {
        return NULL;
    }

    if(vecn(normal) < 3)
    {
        return NULL;
    }

    mat res = mat_new(matrow(m), matcolumn(m));

    m(res, 0, 0) = 1.0 - 2.0 * normal[0] * normal[0];
    m(res, 1, 0) = -2.0 * normal[0] * normal[1];
    m(res, 2, 0) = -2.0 * normal[0] * normal[2];

    m(res, 0, 1) = -2.0 * normal[0] * normal[1];
    m(res, 1, 1) = 1.0 - 2.0 * normal[1] * normal[1];
    m(res, 2, 1) = -2.0 * normal[1] * normal[2];

    m(res, 0, 2) = -2.0 * normal[0] * normal[2];
    m(res, 1, 2) = -2.0 * normal[1] * normal[2];
    m(res, 2, 2) = 1.0 - 2.0 * normal[2] * normal[2];

    mat tmp = mat_multiply_matrix(res, m);
    mat_free(res);
    res = tmp;

    return res;
}

mat mat4_translate_matrix(vec v)
{
    if(vecn(v) < 3)
    {
        return NULL;
    }

    mat res = mat_new(4, 4);
    for(int i = 0; i < 3; i++)
    {
        m(res, i, 3) = v[i];
    }
    return res;
}

mat mat4_rotate_matrix(vec axis, double angle)
{
    if(vecn(axis) < 3)
    {
        return NULL;
    }
    mat res = mat_new(4, 4);
    REAL u, v, w, uu, vv, ww, uv, uw, vw, cs, sn;
    REAL ra = radian(angle);

    vec_normalize(axis);

    u = axis[0];
    v = axis[1];
    w = axis[2];
    uu = u * u;
    vv = v * v;
    ww = w * w;
    uv = u * v;
    uw = u * w;
    vw = v * w;
    cs = cos(ra);
    sn = sin(ra);

    m(res, 0, 0) = uu + (1.0 - uu) * cs;
    m(res, 1, 0) = uv * (1.0 - cs) + w * sn;
    m(res, 2, 0) = uw * (1.0 - cs) - v * sn;

    m(res, 0, 1) = uv * (1.0 - cs) - w * sn;
    m(res, 1, 1) = vv + (1.0 - vv) * cs;
    m(res, 2, 1) = vw * (1.0 - cs) + u * sn;

    m(res, 0, 2) = uw * (1.0 - cs) + v * sn;
    m(res, 1, 2) = vw * (1.0 - cs) - u * sn;
    m(res, 2, 2) = ww + (1.0 - ww) * cs;

    return res;
}

mat mat4_scale_matrix(vec v)
{
    if(vecn(v) < 3)
    {
        return NULL;
    }

    mat res = mat_new(4, 4);

    m(res, 0, 0) = v[0];
    m(res, 1, 1) = v[1];
    m(res, 2, 2) = v[2];

    return res;
}

void mat4_inverse(mat m)
{
    mat tmp = mat4_inverse_matrix(m);
    if(tmp != NULL)
    {
        mat_set(m, tmp);
        mat_free(tmp);
    }
}

void mat4_reflect(mat m, vec normal)
{
    mat tmp = mat4_reflect_matrix(m, normal);
    if(tmp != NULL)
    {
        mat_set(m, tmp);
        mat_free(tmp);
    }
}

void mat4_translate(mat m, vec v)
{
    if(matrow(m) < 3 || matcolumn(m) < 3)
    {
        return;
    }

    for(int i = 0; i < 3; i++)
    {
        m(m, i, 3) += v[i];
    }
}

void mat4_rotate(mat m, vec axis, double angle)
{
    if(matrow(m) < 3 || matcolumn(m) < 3)
    {
        return;
    }

    mat rm = mat4_rotate_matrix(axis, angle);
    if(rm == NULL)
    {
        return;
    }
    mat_transform(m, rm);
    mat_free(rm);
}

void mat4_scale(mat m, vec v)
{
    if(matrow(m) < 3 || matcolumn(m) < 3)
    {
        return;
    }

    mat sm = mat4_scale_matrix(v);
    if(sm == NULL)
    {
        return;
    }
    mat_transform(m, sm);
    mat_free(sm);
}
