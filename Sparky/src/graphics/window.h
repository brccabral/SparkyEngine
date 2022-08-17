#pragma once

#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include "font_manager.h"

namespace sparky
{
	namespace graphics
	{
	#define MAX_KEYS 1024
	#define MAX_BUTTONS 32

		class Window
		{
		private:
			int m_Width, m_Height;
			const char *m_Title;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_KeyState[MAX_KEYS];
			bool m_KeyTyped[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			bool m_MouseState[MAX_BUTTONS];
			bool m_MouseClicked[MAX_BUTTONS];
			double m_MouseX, m_MouseY;

		public:
			Window(const char *title, int width, int height);
			~Window();
			void update();
			void clear() const;
			bool closed() const;

			inline int getWidth() const { return m_Width; };
			inline int getHeight() const { return m_Height; };

			bool isKeyPressed(unsigned int keycode) const;
			bool isKeyTyped(unsigned int keycode) const;
			bool isMousePressed(unsigned int keycode) const;
			bool isMouseClicked(unsigned int keycode) const;
			void getMousePosition(double &x, double &y) const;

		private:
			bool init();

			// callback from GLFW to resize window
			friend static void window_resize(GLFWwindow *window, int width, int height);

			// key_callback is friend so it can access private members
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}