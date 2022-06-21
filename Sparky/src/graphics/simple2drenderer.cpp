#include "simple2drenderer.h"

namespace sparky::graphics
{

    void Simple2Drenderer::submit(const Renderable2D *renderable)
    {
        m_RendererQueue.push_back((StaticSprite *)renderable);
    };
    void Simple2Drenderer::flush()
    {
        while (!m_RendererQueue.empty())
        {
            const StaticSprite *renderable = m_RendererQueue.front();
            renderable->getVAO()->bind();
            renderable->getIBO()->bind();

            Shader shader = renderable->getShader();
            shader.setUniform("ml_matrix", maths::mat4::translation(renderable->getPosition()));
            glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

            renderable->getIBO()->unbind();
            renderable->getVAO()->unbind();

            m_RendererQueue.pop_front();
        }
    };
}