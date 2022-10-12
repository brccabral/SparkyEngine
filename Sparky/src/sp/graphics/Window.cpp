#include "sp/sp.h"
#include "Window.h"
#include <GL/glew.h>

namespace sp
{
	namespace graphics
	{
		std::map<void *, Window *> Window::s_Handles;

		Window::Window(const char *title, uint width, uint height)
			: m_Title(title), m_Width(width), m_Height(height), m_Closed(false), m_EventCallback(nullptr)
		{
			if (!Init())
			{
				SP_ERROR("Failed base Window initialization!");
				return;
			}

			FontManager::Add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));

		#ifdef SPARKY_PLATFORM_WEB
			FreeImage_Initialise();
		#endif

			audio::SoundManager::Init();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_KeyState[i] = false;
				m_LastKeyState[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}
			m_MouseGrabbed = true;
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
				SP_FATAL("Failed to initialize platform!");
				return false;
			}

			glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			SP_INFO("----------------------------------");
			SP_INFO(" OpenGL:");
			SP_INFO("    ", glGetString(GL_VERSION));
			SP_INFO("    ", glGetString(GL_VENDOR));
			SP_INFO("    ", glGetString(GL_RENDERER));
			SP_INFO("----------------------------------");

			return true;
		}

		bool Window::Closed() const
		{
			return m_Closed;
		}

		void Window::UpdateInput()
		{
			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

			memcpy(m_LastKeyState, m_KeyState, MAX_KEYS);
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

			return m_KeyState[keycode];
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

		const bool Window::IsMouseGrabbed() const
		{
			return m_MouseGrabbed;
		}

		void Window::SetMouseGrabbed(bool grabbed)
		{
			m_MouseGrabbed = grabbed;
		}

		void Window::SetEventCallback(const WindowEventCallback &callback)
		{
			m_EventCallback = callback;
		}

		void Window::RegisterWindowClass(void *handle, Window *window)
		{
			s_Handles[handle] = window;
		}

		Window *Window::GetWindowClass(void *handle)
		{
			if (handle == nullptr)
				return s_Handles.begin()->second;

			return s_Handles[handle];
		}

		void Window::SetVsync(bool enabled)
		{
			m_Vsync = enabled;
		}
	}
}