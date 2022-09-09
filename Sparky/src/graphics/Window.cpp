#include "Window.h"

namespace sparky
{
	namespace graphics
	{
		void window_resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

		Window::Window(const char *title, uint width, uint height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!Init())
				glfwTerminate();

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
			glfwTerminate();
		}

		bool Window::Init()
		{
			if (!glfwInit())
			{
				SPARKY_FATAL("Failed to initialize GLFW!");
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				SPARKY_FATAL("Failed to create GLFW window!");
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSwapInterval(0);

		#ifndef SPARKY_PLATFORM_WEB
			if (glewInit() != GLEW_OK) // glewInit needs to be after glfwMakeContextCurrent
			{
				SPARKY_FATAL("Failed to initialize GLEW!");
				return false;
			}
		#endif

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
			return glfwWindowShouldClose(m_Window) == 1;
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
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				SPARKY_ERROR("OpenGL Error: ", error);

			glfwPollEvents();
			glfwSwapBuffers(m_Window);

			UpdateInput();
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

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window *win = (Window *)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		};

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			Window *win = (Window *)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
			Window *win = (Window *)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			Window *win = (Window *)glfwGetWindowUserPointer(window);
			win->m_MousePosition.x = (float)xpos;
			win->m_MousePosition.y = (float)ypos;
		}
	}
}