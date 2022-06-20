#pragma once

// Instead of having a queue that renders sprites one by one
// add all sprites to one batch buffer and render them all at once

#include "renderer2d.h"
#include "renderable2d.h"
#include "buffers/indexbuffer.h"

namespace sparky::graphics
{
// On Windows I can't increase amount of sprites
#define RENDERER_MAX_SPRITES 30000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

    class BatchRederer2D : public Renderer2D
    {
    private:
        GLuint m_VAO;
        GLuint m_VBO;
        IndexBuffer* m_IBO;
        GLsizei m_IndexCount;

        VertexData* m_Buffer;

    public:
        BatchRederer2D();
        ~BatchRederer2D();

        void begin();
        void submit(const Renderable2D* renderable) override;
        void end();
        void flush() override;

    private:
        void init();
    };
} // namespace sparky::graphics
