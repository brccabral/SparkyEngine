#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/maths.h"

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

    mat4 position = mat4::translation(vec3(2, 3, 4));
    position *= mat4::identity();

    vec4& column0 = position.columns[3]; // gets the same address
    vec4 column1 = position.columns[3]; // copy = gets the values, but different address
    std::cout << column0 << std::endl;
    std::cout << column1 << std::endl;
    std::cout << position.elements[12] << std::endl;
    std::cout << position.elements[13] << std::endl;
    std::cout << position.elements[14] << std::endl;
    std::cout << position.elements[15] << std::endl;
    std::cout << &column0.x << std::endl;
    std::cout << &column1.x << std::endl;
    std::cout << &position.elements[12] << std::endl;
    std::cout << &position.columns[3].x << std::endl;

    while (!window.closed())
    {
        window.clear();

        window.update();
    }

    return 0;
}