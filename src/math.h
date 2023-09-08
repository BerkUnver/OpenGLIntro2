#ifndef SRC_MATH_H
#define SRC_MATH_H

typedef struct {
    float x, y, width, height;
} Rect;

typedef struct {
    float r, g, b, a;
} Color;

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    float x, y, z, w;
} Vector4;

typedef struct {
    Vector4 x, y, z, w;
} Matrix4;

Matrix4 matrix4_identity(void);
Matrix4 matrix4_scale(Vector3 scale);
Matrix4 matrix4_translate(Vector3 translate);
Matrix4 matrix4_cross(Matrix4 a, Matrix4 b);
#endif
