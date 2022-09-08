#pragma once

#include <vector>
#include "../Renderer2D.h"
#include "../Renderable2D.h"

namespace sparky
{
	namespace graphics
	{
		class Layer
		{
		protected:
			std::vector<Renderable2D *> m_Renderables;
			Shader *m_Shader;
			maths::mat4 m_ProjectionMatrix;

		public:
			Layer(Renderer2D *renderer, Shader *shader, maths::mat4 projectionMatrix);

			Renderer2D *renderer;

			virtual ~Layer();
			virtual Renderable2D *Add(Renderable2D *renderable);
			virtual void Render();

			inline const std::vector<Renderable2D *> &GetRenderables() const { return m_Renderables; }

			inline void SetMask(const Mask *mask) const { renderer->SetMask(mask); };
		};
	}
}