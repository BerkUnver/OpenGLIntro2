#include <GL/gl.h>
#include "draw.h"
#include "draw_gl.h"
#include "math.h"

Shader immediate_shader;

// init drawing module
void draw_init(void) {
    char *immediate_shader_source = 
        "#if defined SHADER_VERTEX\n"
        "\n"
        "layout (location = 0) in vec3 vertex;\n"
        "layout (location = 1) in vec4 color;\n"
        "\n"
        "uniform mat4 transform;\n"
        "\n"
        "out vec4 fragment_color;\n"
        "\n"
        "void main() {\n"
        "   gl_Position = vec4(vertex, 1) * transform;\n"
        "   fragment_color = color;\n"
        "}\n"
        "\n"
        "#elif defined SHADER_FRAGMENT\n"
        "\n"
        "in vec4 fragment_color;\n"
        "\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = fragment_color;\n"
        "}\n"
        "#endif\n";

    shader_load(immediate_shader_source, &immediate_shader); 
    shader_use(&immediate_shader);

    Matrix4 mat_corner = matrix4_translate((Vector3) {-1, -1, 0});
    Matrix4 mat_corner_scaled = matrix4_scale((Vector3) {2, 2, 1});
    Matrix4 mat_0x0x1x1 = matrix4_cross(mat_corner, mat_corner_scaled);
    Matrix4 mat_monitor = matrix4_scale((Vector3) {1.0f / 1920.0f, 1.0f / 1080.0f, 0}); // @todo don't hardcode
    Matrix4 mat = matrix4_cross(mat_0x0x1x1, mat_monitor);

    shader_set_uniform_matrix4(immediate_shader.loc_transform, &mat);
}


// deinit drawing module
void draw_free(void) {
    shader_free(&immediate_shader);
}
