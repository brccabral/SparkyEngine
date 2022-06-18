#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"

int main()
{
    using namespace sparky;
    using namespace graphics;

    Window window("Sparky!", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    while (!window.closed())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        window.update();
    }

    return 0;
}