#include "render/shader.h"
#include "glad/glad.h"


unsigned int shader_pool[SHADER_COUNT];


int check_shader_compile_errors(unsigned int id, int is_program)
{
    int success;
    char log[1024];
    if (is_program)
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, log);
            return FAILED;
        }
    }
    else
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, NULL, log);
            return FAILED;
        }
    }
    return SUCCESSED;
}

void shader_bind(enum SHADER_TYPE t)
{
    if(t >= SHADER_COUNT)
    {
        return;
    }
    glUseProgram(shader_pool[t]);
}

void shader_unbind()
{
    glUseProgram(0);
}

void shader_set_int(unsigned int id, char *name, int value)
{

    glUniform1i(glGetUniformLocation(id, name), value);
}



