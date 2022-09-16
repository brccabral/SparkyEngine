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

class TestLayer : public sparky::graphics::Layer2D
{
private:
	sparky::graphics::Label *m_Fps;
	sparky::graphics::Label **debugInfo;
public:
	TestLayer();
	~TestLayer();

	void OnInit(sparky::graphics::Renderer2D &renderer, sparky::graphics::Shader &shader) override;

	void OnTick() override;
	void OnUpdate() override;
	bool OnEvent(const sparky::events::Event &event) override;
	void OnRender(sparky::graphics::Renderer2D &renderer) override;
};