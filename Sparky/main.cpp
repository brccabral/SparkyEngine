#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"

int main()
{
    using namespace sparky;
    using namespace graphics;

    Window window("Sparky!", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    while (!window.closed())
    {
        window.clear();

        std::cout << "Key A: " << window.isKeyPressed(GLFW_KEY_A) << std::endl;
        std::cout << "Mouse Left: " << window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT) << std::endl;

        window.update();
    }

    return 0;
}