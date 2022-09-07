#include "layer.h"

namespace sparky
{
	namespace graphics
	{
		Layer::Layer(Renderer2D *renderer, Shader *shader, maths::mat4 projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->enable();
			m_Shader->setUniform("pr_matrix", m_ProjectionMatrix);

		#ifdef SPARKY_PLATFORM_WEB
			m_Shader->setUniform("texture_0", 0);
			m_Shader->setUniform("texture_1", 1);
			m_Shader->setUniform("texture_2", 2);
			m_Shader->setUniform("texture_3", 3);
			m_Shader->setUniform("texture_4", 4);
			m_Shader->setUniform("texture_5", 5);
			m_Shader->setUniform("texture_6", 6);
			m_Shader->setUniform("texture_7", 7);
		#else
			GLint texIDs[] = {
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			m_Shader->setUniform("textures", texIDs, 32);
		#endif

			m_Shader->disable();
		};

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;
			for (uint i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}
		};

		Renderable2D *Layer::add(Renderable2D *renderable)
		{
			m_Renderables.push_back(renderable);
			return renderable;
		};

		void Layer::render()
		{
			m_Shader->enable();
			m_Renderer->begin();
			for (const Renderable2D *renderable : m_Renderables)
				renderable->submit(m_Renderer);

			m_Renderer->end();
			m_Renderer->flush();
		};

	}
}