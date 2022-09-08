#pragma once

#include <iostream>
#include <sparkygl.h>
#include "FontManager.h"
#include <audio/SoundManager.h>
#include <maths/vec2.h>
#include "TextureManager.h"
#include "../embedded/Embedded.h"

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
			maths::vec2 m_MousePosition;

		public:
			Window(const char *title, int width, int height);
			~Window();
			void Update();
			void Clear() const;
			bool Closed() const;
			void UpdateInput();

			inline int GetWidth() const { return m_Width; };
			inline int GetHeight() const { return m_Height; };

			bool IsKeyPressed(uint keycode) const;
			bool IsKeyTyped(uint keycode) const;
			bool IsMousePressed(uint keycode) const;
			bool IsMouseClicked(uint keycode) const;
			const maths::vec2 &GetMousePosition() const;
		private:
			bool Init();

			// callback from GLFW to resize window
			friend void window_resize(GLFWwindow *window, int width, int height);

			// key_callback is friend so it can access private members
			friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};

	}
}