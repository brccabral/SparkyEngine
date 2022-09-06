#pragma once

#ifdef SPARKY_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

#include "graphics/label.h"
#include "graphics/sprite.h"
#include "graphics/batchrenderer2d.h"
#include "graphics/window.h"
#include "graphics/layers/layer.h"
#include "graphics/layers/group.h"
#include "graphics/texture_manager.h"

#include "audio/sound.h"
#include "audio/sound_manager.h"

#include "maths/maths.h"

#include "utils/timer.h"

#ifdef SPARKY_EMSCRIPTEN
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
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;

	public:
		void start()
		{
			init();
			run();
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

		graphics::Window *createWindow(const char *title, int width, int height)
		{
			m_Window = new graphics::Window(title, width, height);
			return m_Window;
		}

		// Runs once upon initialization
		virtual void init() = 0;
		// Runs once per second
		virtual void tick() {};
		// Runs 60 times per second
		virtual void update() {};
		// Runs as fast as possible (unless vsync is enabled)
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; };
		const unsigned int getUPS() const { return m_UpdatesPerSecond; };

	private:
		void run()
		{
			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;

			unsigned int frames = 0;
			unsigned int updates = 0;
		#ifdef SPARKY_EMSCRIPTEN
			std::function<void()> mainLoop = [&]()
			{
		#else
			while (!m_Window->closed())
			{
		#endif
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}

				render();
				m_Window->update();

				frames++;
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;

					timer += 1.0f;

					frames = 0;
					updates = 0;

					tick();
				}
		#ifdef SPARKY_EMSCRIPTEN
			};
			emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
		#else
			}
		#endif
		}
	};
}