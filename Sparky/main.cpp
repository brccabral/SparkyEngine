#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/vec2.h"

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

    vec2 vector2(1.0f, 2.0f);
    vector2.add(vec2(5, 2)).add(vec2(1, 1));

    vec2 a(1.0f, 2.0f);
    vec2 b(2, 4);
    vec2 c = a + b;

    std::cout << vector2 << std::endl;
    std::cout << c << std::endl; \

        while (!window.closed())
        {
            window.clear();

            window.update();
        }

    return 0;
}