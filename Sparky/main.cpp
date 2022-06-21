#include <iostream>
#include <vector>
#include <time.h>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shader.h"
#include "src/graphics/sprite.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/utils/timer.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#define TEST_50K_SPRITE 0

int main()
{
    using namespace sparky;
    using namespace graphics;
    using namespace maths;

    Window window("Sparky!", 960, 540);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader *s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Shader *s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Shader& shader = *s;
    Shader& shader2 = *s2;
    //shader.setUniform("light_pos", vec2(4.0f, 1.5f));
    shader2.setUniform("light_pos", vec2(4.0f, 1.5f));

    TileLayer layer(&shader);
#if TEST_50K_SPRITE
    for (float y = -9.0f; y < 9.0f; y+=0.1)
    {
        for (float x = -16.0f; x < 16.0f; x += 0.1) {
            layer.add(new Sprite(x, y, 0.09f, 0.09f, vec4(rand()%1000 / 1000.0f, 0, 1, 1)));
        }
    }
#else
    mat4 transform = mat4::translation(vec3(-15.0f, 5.0f, 0.0f)) * mat4::rotation(45.0f, vec3(0, 0, 1));
    Group *group = new Group(transform);
    group->add(new Sprite(0, 0, 6, 3, vec4(1, 1, 1, 1)));

    Group* button = new Group(mat4::translation(vec3(0.5, 0.5, 0.0f)) * mat4::rotation(-90.0f, vec3(0, 0, 1)));
    button->add(new Sprite(0.0f, 0.0f, 5.0f, 2.0f, vec4(1, 0, 1, 1)));
    button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, vec4(0.2f, 0.3f, 0.8f, 1)));
    group->add(button);

    layer.add(group);
#endif


    TileLayer layer2(&shader2);
    layer2.add(new Sprite(-2,-2,4,4, vec4(1, 0, 1, 1)));


    double x, y;

    Timer time;
    float timer = 0.0f;
    unsigned int frames = 0;
    while (!window.closed())
    {
        window.clear();
        window.getMousePosition(x, y);
        //shader.setUniform("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
        shader.enable();
        shader2.setUniform("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
        shader2.enable();

        layer.render();
        //layer2.render();

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