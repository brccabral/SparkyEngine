#include <iostream>
#include <vector>
#include <time.h>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shader.h"
#include "src/graphics/sprite.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/utils/timer.h"

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

    srand(time(NULL));
    std::vector<Renderable2D*> sprites;
    for (float y = 0; y < 9.0f; y+=0.05)
    {
        for (float x = 0; x < 16.0f; x+=0.05)
        {
            sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }

    BatchRenderer2D renderer;

    shader.setUniform("light_pos", vec2(4.0f, 1.5f));
    shader.setUniform("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    double x, y;

    Timer time;
    float timer = 0.0f;
    unsigned int frames = 0;
    while (!window.closed())
    {
        // this is to show that mat4 has problems
        mat4 mat = mat4::translation(vec3(5, 5, 5));
        mat = mat * mat4::rotation(time.elapsed() * 50.0f, vec3(0, 0, 1));
        mat = mat * mat4::translation(vec3(-5, -5, -5));
        shader.setUniform("ml_matrix", mat);

        window.clear();
        window.getMousePosition(x, y);
        shader.setUniform("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
        renderer.begin();
        for (int i = 0; i < sprites.size(); i++)
        {
            renderer.submit(sprites[i]);
        }
        renderer.end();
        renderer.flush();

        window.update();

        frames++;
        if (time.elapsed() - timer > 1.0f)
        {
            timer += 1.0f;
            printf("%d fps\n", frames);
            frames = 0;
        }
    }

    return 0;
}