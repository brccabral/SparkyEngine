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

    double x, y;

    while (!window.closed())
    {
        window.clear();

        window.getMousePosition(x, y);

        std::cout << "x: " << x << " y: " << y << std::endl;

        window.update();
    }

    return 0;
}