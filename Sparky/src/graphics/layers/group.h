#pragma once

// Group to add Sprites relative one another

#include "../renderable2d.h"
#include <vector>

namespace sparky::graphics
{
	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D *> m_Renderables;
		maths::mat4 m_TransformationMatrix;

	public:
		Group(const maths::mat4 &transform);
		~Group();

		void add(Renderable2D *renderable);
		void submit(Renderer2D *renderer) const override;
	};
}