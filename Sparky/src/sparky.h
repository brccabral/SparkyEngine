#pragma once

#ifdef SPARKY_PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

#include "graphics/Label.h"
#include "graphics/Sprite.h"
#include "graphics/BatchRenderer2D.h"
#include "graphics/layers/Layer.h"
#include "graphics/layers/Group.h"
#include "graphics/TextureManager.h"
#include "graphics/Window.h"

#include "graphics/shaders/ShaderFactory.h"

#include "audio/Sound.h"
#include "audio/SoundManager.h"

#include "maths/maths.h"
#include <utils/Log.h>
#include "utils/Timer.h"

#ifdef SPARKY_PLATFORM_WEB
static void dispatch_main(void *fp)
{
	std::function<void()> *func = (std::function<void()>*)fp;
	(*func)();
}
#endif

namespace sparky
{
	class Sparky
	{
	private:
		graphics::Window *m_Window;
		Timer *m_Timer;
		uint m_FramesPerSecond, m_UpdatesPerSecond;

	public:
		void Start()
		{
			Init();
			Run();
		}

	protected:
		Sparky()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0), m_Window(nullptr), m_Timer(nullptr)
		{

		}

		virtual ~Sparky()
		{
			delete m_Timer;
			delete m_Window;
		}

		graphics::Window *CreateWindow(const char *title, int width, int height)
		{
			m_Window = new graphics::Window(title, width, height);
			return m_Window;
		}

		// Runs once upon initialization
		virtual void Init() = 0;
		// Runs once per second
		virtual void Tick() {};
		// Runs 60 times per second
		virtual void Update() {};
		// Runs as fast as possible (unless vsync is enabled)
		virtual void Render() = 0;

		const uint GetFPS() const { return m_FramesPerSecond; };
		const uint GetUPS() const { return m_UpdatesPerSecond; };

	private:
		void Run()
		{
			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;

			uint frames = 0;
			uint updates = 0;
		#ifdef SPARKY_PLATFORM_WEB
			std::function<void()> mainLoop = [&]()
			{
			#else
			while (!m_Window->Closed())
			{
			#endif
				m_Window->Clear();
				if (m_Timer->Elapsed() - updateTimer > updateTick)
				{
					Update();
					updates++;
					updateTimer += updateTick;
				}

				Render();
				m_Window->Update();

				frames++;
				if (m_Timer->Elapsed() - timer > 1.0f)
				{
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;

					timer += 1.0f;

					frames = 0;
					updates = 0;

					Tick();
				}
			#ifdef SPARKY_PLATFORM_WEB
			};
			emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
		#else
			}
		#endif
		}
	};
}