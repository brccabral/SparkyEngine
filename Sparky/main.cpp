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

    vec2 a(1.0f, 2.0f);
    vec2 b(2, 4);

    vec2 g(3, 7);
    vec2 h(4, 9);
    std::cout << g << std::endl;
    std::cout << h << std::endl;
    g -= h;
    std::cout << g << std::endl;

    vec2 k(1.0f, 2.0f);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << k << std::endl;
    std::cout << (a != b) << std::endl;
    std::cout << (a == k) << std::endl;

    vec2 c = a + b + g;
    // c.x = 100.0f;

    std::cout << a << std::endl;
    std::cout << c << std::endl;

    while (!window.closed())
    {
        window.clear();

        window.update();
    }

    return 0;
}