#include "math.h"
#include <stdio.h>

Matrix4 matrix4_identity(void) {
    return (Matrix4) {
        .x = (Vector4) {1, 0, 0, 0},
        .y = (Vector4) {0, 1, 0, 0},
        .z = (Vector4) {0, 0, 1, 0},
        .w = (Vector4) {0, 0, 0, 1}
    };
}

Matrix4 matrix4_scale(Vector3 scale) {
    return (Matrix4) {
        .x = (Vector4) {scale.x, 0, 0, 0},
        .y = (Vector4) {0, scale.y, 0, 0},
        .z = (Vector4) {0, 0, scale.z, 0},
        .w = (Vector4) {0, 0, 0, 1}
    };
}

Matrix4 matrix4_translate(Vector3 translate) {
    return (Matrix4) {
        .x = (Vector4) {1, 0, 0, 0},
        .y = (Vector4) {0, 1, 0, 0},
        .z = (Vector4) {0, 0, 1, 0},
        .w = (Vector4) {translate.x, translate.y, translate.z, 1},
    };
}

Matrix4 matrix4_cross(Matrix4 a, Matrix4 b) {
    Matrix4 result;
    
    // The reason they are backwards is because raylib had them backwards for some reason
    result.x.x = b.x.x*a.x.x + b.x.y*a.y.x + b.x.z*a.z.x + b.x.w*a.w.x;
    result.x.y = b.x.x*a.x.y + b.x.y*a.y.y + b.x.z*a.z.y + b.x.w*a.w.y;
    result.x.z = b.x.x*a.x.z + b.x.y*a.y.z + b.x.z*a.z.z + b.x.w*a.w.z;
    result.x.w = b.x.x*a.x.w + b.x.y*a.y.w + b.x.z*a.z.w + b.x.w*a.w.w;
    result.y.x = b.y.x*a.x.x + b.y.y*a.y.x + b.y.z*a.z.x + b.y.w*a.w.x;
    result.y.y = b.y.x*a.x.y + b.y.y*a.y.y + b.y.z*a.z.y + b.y.w*a.w.y;
    result.y.z = b.y.x*a.x.z + b.y.y*a.y.z + b.y.z*a.z.z + b.y.w*a.w.z;
    result.y.w = b.y.x*a.x.w + b.y.y*a.y.w + b.y.z*a.z.w + b.y.w*a.w.w;
    result.z.x = b.z.x*a.x.x + b.z.y*a.y.x + b.z.z*a.z.x + b.z.w*a.w.x;
    result.z.y = b.z.x*a.x.y + b.z.y*a.y.y + b.z.z*a.z.y + b.z.w*a.w.y;
    result.z.z = b.z.x*a.x.z + b.z.y*a.y.z + b.z.z*a.z.z + b.z.w*a.w.z;
    result.z.w = b.z.x*a.x.w + b.z.y*a.y.w + b.z.z*a.z.w + b.z.w*a.w.w;
    result.w.x = b.w.x*a.x.x + b.w.y*a.y.x + b.w.z*a.z.x + b.w.w*a.w.x;
    result.w.y = b.w.x*a.x.y + b.w.y*a.y.y + b.w.z*a.z.y + b.w.w*a.w.y;
    result.w.z = b.w.x*a.x.z + b.w.y*a.y.z + b.w.z*a.z.z + b.w.w*a.w.z;
    result.w.w = b.w.x*a.x.w + b.w.y*a.y.w + b.w.z*a.z.w + b.w.w*a.w.w;

    float *ptr = (float *) &result;

    for (int i = 0; i < 4; i++) {
        printf("[%f, %f, %f, %f]\n", ptr[i*4], ptr[i*4 + 1], ptr[i*4 + 2], ptr[i*4 + 3]);
    }
    
    return result;
}
