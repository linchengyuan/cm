#ifndef CAMERA_H
#define CAMERA_H

#include "math/mat.h"

typedef struct camera_info
{
    mat m;
    vec viewport;
    REAL rotate_speed, scale_speed;
    REAL fov, aspect_ratio;
} camera_info;

#endif // CAMERA_H
