#pragma once

#include <sp/app/Application.h>
#include <sp/sparky.h>
#include <sp/events/Event.h>
#include <sp/graphics/layers/Layer2D.h>
#include <sp/graphics/Label.h>
#include <sp/graphics/Renderer2D.h>
#include <sp/graphics/BatchRenderer2D.h>
#include <sp/graphics/shaders/ShaderFactory.h>
#include <sp/graphics/FontManager.h>
#include <sp/graphics/Sprite.h>

class TestLayer : public sp::graphics::Layer2D
{
private:
	sp::graphics::Label *m_Fps;
	sp::graphics::Label **debugInfo;
public:
	TestLayer();
	~TestLayer();

	void OnInit(sp::graphics::Renderer2D &renderer, sp::graphics::Shader &shader) override;

	void OnTick() override;
	void OnUpdate() override;
	bool OnEvent(const sp::events::Event &event) override;
	void OnRender(sp::graphics::Renderer2D &renderer) override;
};