#include "glad/glad.h"

#include "draw.h"
#include "draw_gl.h"
#include "log.h"

bool shader_load(char *shader_source, Shader *out) {
    char shader_log[1024];
    
    bool success = false;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    char *vertex_source[] = {
        "#version 330 core\n",
        "#define SHADER_VERTEX\n",
        shader_source
    };
    glShaderSource(vertex_shader, sizeof(vertex_source) / sizeof(*vertex_source), (const char * const *) vertex_source, NULL);
    glCompileShader(vertex_shader);

    int vertex_success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_success);
    if (!vertex_success) {
        glGetShaderInfoLog(vertex_shader, sizeof(shader_log), NULL, shader_log);
        logprint("opengl", "%s", shader_log);
        goto delete_shaders;
    }
    
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char *fragment_source[] = {
        "#version 330 core\n",
        "#define SHADER_FRAGMENT\n",
        shader_source
    };
    glShaderSource(fragment_shader, sizeof(fragment_source) / sizeof(*fragment_source), (const char * const *) fragment_source, NULL);
    glCompileShader(fragment_shader);
    
    int fragment_success;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_success);
    if (!fragment_success) {
        glGetShaderInfoLog(fragment_shader, sizeof(shader_log), NULL, shader_log);
        logprint("opengl", "%s", shader_log);
        goto delete_shaders;
    }

    GLuint shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    int link_success;
    glGetProgramiv(shader, GL_LINK_STATUS, &link_success);
    if (!link_success) {
        glGetProgramInfoLog(shader, sizeof(shader_log), NULL, shader_log);
        logprint("opengl", "%s", shader_log);
        glDeleteProgram(shader);
        goto delete_shaders;
    }
    success = true;

delete_shaders:
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    if (success) {
        *out = (Shader) {
            .handle = shader,
            .loc_transform = glGetUniformLocation(shader, "transform")
        };
    }

    return success;
}

void shader_free(Shader *shader) {
    glDeleteProgram(shader->handle);
}

void shader_use(Shader *shader) {
    glUseProgram(shader->handle);
}

void shader_set_uniform_matrix4(int loc, Matrix4 *mat) {
    glUniformMatrix4fv(loc, 1, GL_TRUE, (float *) mat);
}

void draw_immediate_rect(Rect rect, Color color) {
    GLuint vao;
    GLuint vbo;
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float verticies[] = {
        rect.x, rect.y, 0,                              color.r, color.g, color.b, color.a,
        rect.x, rect.y + rect.height, 0,                color.r, color.g, color.b, color.a,
        rect.x + rect.width, rect.y, 0,                 color.r, color.g, color.b, color.a,
        rect.x + rect.width, rect.y, 0,                 color.r, color.g, color.b, color.a,
        rect.x, rect.y + rect.height, 0,                color.r, color.g, color.b, color.a,
        rect.x + rect.width, rect.y + rect.height, 0,   color.r, color.g, color.b, color.a
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float))); 
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(verticies) / sizeof(*verticies));
    
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
