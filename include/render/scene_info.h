#ifndef SCENE_INFO_H
#define SCENE_INFO_H

#include "render/camera.h"
#include "render/boundingsphere.h"
#include "render/rendercallback.h"


typedef VOID *vertices;


enum RENDER_TYPE
{
    RENDER_NORMAL,
    RENDER_DTM,
    RENDER_OIT,
    RENDER_PICK,


    RENDER_COUNT
};

typedef struct drawable
{
    unsigned int id;
    mat model_matrix;
    boundingsphere *bsphere;

} drawable;




typedef struct scene_node
{
    enum RENDER_TYPE render_type;
    boundingsphere *bsphere;
    render_info info;
    drawable* models;
    struct scene_node **children;
} scene_node;


typedef struct scene_info
{
    scene_node *root;

} scene_info;


#endif // SCENE_INFO_H
