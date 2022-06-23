#include "renderable2d.h"

namespace sparky::graphics
{
	Renderable2D::Renderable2D()
		: m_Texture(nullptr)
	{
		setUVDefaults();
	};
	Renderable2D::Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
	{
		setUVDefaults();
	};
	Renderable2D::~Renderable2D() {};

	void Renderable2D::setUVDefaults()
	{
		m_UV.push_back(maths::vec2(0, 0));
		m_UV.push_back(maths::vec2(0, 1));
		m_UV.push_back(maths::vec2(1, 1));
		m_UV.push_back(maths::vec2(1, 0));
	};
} // namespace sparky::graphics