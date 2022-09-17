#include "Renderable2D.h"

namespace sp
{
	namespace graphics
	{
		Renderable2D::Renderable2D()
			: m_Texture(nullptr)
		{
			SetUVDefaults();
		};
		Renderable2D::Renderable2D(maths::vec3 position, maths::vec2 size, uint color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
		{
			SetUVDefaults();
		};
		Renderable2D::~Renderable2D() {};

		void Renderable2D::SetUVDefaults()
		{
			m_UV.push_back(maths::vec2(0.0f, 0.0f));
			m_UV.push_back(maths::vec2(0.0f, 1.0f));
			m_UV.push_back(maths::vec2(1.0f, 1.0f));
			m_UV.push_back(maths::vec2(1.0f, 0.0f));
		};
	}
}