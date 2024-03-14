#include "pch.h"
#include "component.h"

mat4 transform_get_matrix(transform_component* tc)
{
    return mat4_mul(mat4_translation(tc->position), mat4_mul(mat4_euler_xyz(tc->rotation), mat4_scale(tc->scale)));
}