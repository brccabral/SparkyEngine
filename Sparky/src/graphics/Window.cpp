#include "Window.h"

namespace sparky
{
	namespace graphics
	{
		std::map<void *, Window *> Window::s_Handles;

		Window::Window(const char *title, uint width, uint height)
			: m_Title(title), m_Width(width), m_Height(height), m_Closed(false)
		{
			if (!Init())
			{
				SPARKY_ERROR("Failed base Window initialization!");
				return;
			}

			FontManager::Add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));

		#ifdef SPARKY_PLATFORM_WEB
			FreeImage_Initialise();
		#endif

			audio::SoundManager::Init();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}
		}

		Window::~Window()
		{
			FontManager::Clean();
			TextureManager::Clean();
			audio::SoundManager::Clean();
		}

		bool Window::Init()
		{
			if (!PlatformInit())
			{
				SPARKY_FATAL("Failed to initialize platform!");
				return false;
			}

			glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			SPARKY_INFO("----------------------------------");
			SPARKY_INFO(" OpenGL:");
			SPARKY_INFO("    ", glGetString(GL_VERSION));
			SPARKY_INFO("    ", glGetString(GL_VENDOR));
			SPARKY_INFO("    ", glGetString(GL_RENDERER));
			SPARKY_INFO("----------------------------------");

			return true;
		}

		bool Window::Closed() const
		{
			return m_Closed;
		}

		void Window::UpdateInput()
		{
			for (int i = 0; i < MAX_KEYS; i++)
				m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

			memcpy(m_KeyState, m_Keys, MAX_KEYS);

			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

			memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
		}

		void Window::Update()
		{
			PlatformUpdate();
			audio::SoundManager::Update();
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::IsKeyPressed(uint keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		bool Window::IsKeyTyped(uint keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_KeyTyped[keycode];
		}

		bool Window::IsMouseClicked(uint button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseClicked[button];
		}

		bool Window::IsMousePressed(uint button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		const maths::vec2 &Window::GetMousePosition() const
		{
			return m_MousePosition;
		}

		void Window::RegisterWindowClass(void *handle, Window *window)
		{
			s_Handles[handle] = window;
		}

		Window *Window::GetWindowClass(void *handle)
		{
			return s_Handles[handle];
		}
	}
}