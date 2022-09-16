#pragma once

#include <app/Application.h>
#include <sparky.h>
#include <events/Event.h>
#include <graphics/layers/Layer2D.h>
#include <graphics/Label.h>
#include <graphics/Renderer2D.h>
#include <graphics/BatchRenderer2D.h>
#include <graphics/shaders/ShaderFactory.h>
#include <graphics/FontManager.h>
#include <graphics/Sprite.h>

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