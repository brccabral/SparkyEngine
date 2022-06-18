#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"

int main()
{
    using namespace sparky;
    using namespace graphics;

    Window window("Sparky!", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    std::cout << glGetString(GL_VERSION) << std::endl;

    while (!window.closed())
    {
        window.clear();
        window.update();
    }

    return 0;
}