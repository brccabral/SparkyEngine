#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/maths.h"

#include "src/graphics/shader.h"
#include "src/graphics/simple2drenderer.h"

#include "src/graphics/sprite.h"
#include "src/graphics/batchrenderer2d.h"

int main()
{
    using namespace sparky;
    using namespace graphics;
    using namespace maths;

    Window window("Sparky!", 960, 540);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.enable();
    shader.setUniform("pr_matrix", ortho);

    Sprite sprite(5, 5, 4, 4, vec4(1, 0, 1, 1));
    Sprite sprite2(7, 1, 2, 3, vec4(0.2f, 0, 1, 1));
    BatchRederer2D renderer;

    shader.setUniform("light_pos", vec2(4.0f, 1.5f));
    shader.setUniform("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    double x, y;

    while (!window.closed())
    {
        renderer.begin();
        window.clear();
        window.getMousePosition(x, y);
        shader.setUniform("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
        renderer.submit(&sprite);
        renderer.submit(&sprite2);
        renderer.end();
        renderer.flush();

        window.update();
    }

    return 0;
}