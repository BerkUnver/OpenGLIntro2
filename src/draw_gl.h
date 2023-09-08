#ifndef SRC_DRAW_GL_H
#define SRC_DRAW_GL_H

#include <stdbool.h>
#include <GL/gl.h>

typedef struct {
    GLuint handle;
    int loc_transform;
} Shader;

bool shader_load(char *src, Shader *out);
void shader_free(Shader *shader);
void shader_use(Shader *shader);
void shader_set_uniform_matrix4(int loc, Matrix4 *mat);

#endif
