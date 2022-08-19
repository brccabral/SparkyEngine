#pragma once

#include "graphics/window.h"

namespace sparky
{
	class Sparky
	{
	private:
		graphics::Window *m_Window;
	protected:
		Sparky()
		{

		}

		virtual ~Sparky()
		{
			delete m_Window;
		}

		graphics::Window *createWindow(const char *title, int width, int height)
		{
			m_Window = new graphics::Window(title, width, height);
			return m_Window;
		}

		void start()
		{
			init();
			run();
		}

		// Runs once upon initialization
		virtual void init() = 0;
		// Runs once per second
		virtual void tick() = 0;
		// Runs 60 times per second
		virtual void update() = 0;
		// Runs as fast as possible (unless vsync is enabled)
		virtual void render() = 0;
	private:
		void run()
		{
			
		}
	};
}