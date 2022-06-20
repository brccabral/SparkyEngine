#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/graphics/shader.h"

int main()
{
    using namespace sparky;
    using namespace graphics;
    using namespace maths;

    Window window("Sparky!", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");

    while (!window.closed())
    {
        window.clear();

        window.update();
    }

    return 0;
}