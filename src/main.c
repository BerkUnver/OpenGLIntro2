#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "glfw3.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "CGui", NULL, NULL);
    if (!window) {
        printf("Failed to open GLFW window.\n");
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to load OpenGL extensions.\n");
        return EXIT_FAILURE;
    }

    glViewport(0, 0, 1920, 1080);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
