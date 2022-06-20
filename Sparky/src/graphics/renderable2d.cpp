#include "renderable2d.h"

namespace sparky::graphics
{
    Renderable2D::Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
        : m_Position(position), m_Size(size), m_Color(color) {};
    Renderable2D::~Renderable2D() {};
}