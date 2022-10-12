#pragma once

#include "sp/sp.h"
#include "sp/Common.h"
#include "sp/Types.h"

#include "sp/graphics/Window.h"
#include "sp/graphics/layers/Layer.h"
#include "sp/utils/Timer.h"

namespace sp
{
	class SP_API Application
	{
	public:
		graphics::Window *window;
	private:
		static Application *s_Instance;

		bool m_Running, m_Suspended;
		Timer *m_Timer;
		uint m_UpdatesPerSecond, m_FramesPerSecond;

		const char *m_Name;
		uint m_Width, m_Height;

		std::vector<graphics::Layer *> m_LayerStack;
		std::vector<graphics::Layer *> m_OverlayStack;
	public:
		Application(const char *name, uint width, uint height);
		virtual ~Application();

		virtual void Init();

		void Start();
		void Suspend();
		void Resume();
		void Stop();
		
		const uint GetFPS() const { return m_FramesPerSecond; }
		const uint GetUPS() const { return m_UpdatesPerSecond; }

		void PushLayer(graphics::Layer *layer);
		graphics::Layer *PopLayer();

		void PushOverlay(graphics::Layer *layer);
		graphics::Layer *PopOverlay();

		inline static Application &GetApplication() { return *s_Instance; }
	private:
		void Run();

		void OnTick();
		void OnUpdate();
		void OnRender();
	};
}