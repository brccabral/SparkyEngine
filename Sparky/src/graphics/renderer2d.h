#pragma once

#include <vector>
#include <sparkygl.h>
#include "texture.h"
#include "font.h"
#include "../maths/maths.h"
#include "mask.h"

namespace sparky
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<maths::mat4> m_TransformationStack;
			const maths::mat4 *m_TransformationBack;
			const Mask *m_Mask;

		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(maths::mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
				m_Mask = nullptr;
			};

		public:
			virtual ~Renderer2D() {};

			// apply parent transformation to child
			void push(const maths::mat4 &matrix, bool do_override = false)
			{
				if (do_override)
					m_TransformationStack.push_back(matrix);
				else
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
				m_TransformationBack = &m_TransformationStack.back();
			};

			void pop()
			{
				if (m_TransformationStack.size() > 1) // keep identity on stack
					m_TransformationStack.pop_back();
				m_TransformationBack = &m_TransformationStack.back();
			};

			virtual void begin() {};
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void end() {};
			virtual void flush() = 0;

			virtual void drawString(const std::string &text, maths::vec3 position, const Font &font, uint color) {};

			virtual void setMask(const Mask *mask)
			{
				m_Mask = mask;
			}
		};
	}
}