#ifndef SHADER_H
#define SHADER_H

#include "math/mat.h"

enum SHADER_TYPE
{
    SHADER_DEFAUTL = 0,
    SHADER_PICK,
    SHADER_DTM,
    SHADER_AXIS,
    SHADER_OIT,

    SHADER_COUNT
};


int shader_init();
void shader_bind(enum SHADER_TYPE t);
void shader_unbind();

void shader_set_int(unsigned int id, char *name, int value);
void shader_set_float(unsigned int id, char *name, float value);
void shader_set_double(unsigned int id, char *name, double value);
void shader_set_real(unsigned int id, char *name, REAL value);
void shader_set_vec2(unsigned int id, char *name, vec value);
void shader_set_vec3(unsigned int id, char *name, vec value);
void shader_set_vec4(unsigned int id, char *name, vec value);
void shader_set_mat3(unsigned int id, char *name, mat value);
void shader_set_mat4(unsigned int id, char *name, mat value);

#endif // SHADER_H
