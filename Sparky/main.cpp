#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/graphics/shader.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

int main()
{
    using namespace sparky;
    using namespace graphics;
    using namespace maths;

    Window window("Sparky!", 960, 540);

    // draw two triangles to form a rectangle
    GLfloat vertices[] = {
        0, 0, 0,
        0, 3, 0,
        8, 3, 0,
        8, 0, 0 };
    // indices of vertices in order to create two triangles
    // that will form a rectangle
    GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

    VertexArray vao;
    Buffer* vbo = new Buffer(vertices, 4 * 3, 3);
    IndexBuffer ibo(indices, 6);

    vao.addBuffer(vbo, 0);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.enable();
    shader.setUniform("pr_matrix", ortho);
    shader.setUniform("ml_matrix", mat4::translation(vec3(4, 3, 0)));

    shader.setUniform("light_pos", vec2(4.0f, 1.5f));
    shader.setUniform("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    double x, y;

    while (!window.closed())
    {
        window.clear();
        window.getMousePosition(x, y);
        shader.setUniform("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

        vao.bind();
        ibo.bind();
        shader.setUniform("ml_matrix", mat4::translation(vec3(4, 3, 0)));
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        shader.setUniform("ml_matrix", mat4::translation(vec3(0, 0, 0)));
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        ibo.unbind();
        vao.unbind();

        window.update();
    }

    return 0;
}