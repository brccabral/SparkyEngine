#include "window.h"
#include <iostream>

namespace sparky
{
    namespace graphics
    {
        // callback from GLFW to resize window
        void window_resize(GLFWwindow* window, int width, int height);

        // keyboard input callback from GLFW
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        bool Window::m_Keys[MAX_KEYS];
        bool Window::m_MouseButtons[MAX_BUTTONS];
        double Window::m_MouseX, Window::m_MouseY;

        Window::Window(const char* title, int width, int height)
        {
            m_Title = title;
            m_Width = width;
            m_Height = height;
            if (!init())
                glfwTerminate();

            for (int i = 0; i < MAX_KEYS; i++)
                m_Keys[i] = false;

            for (int i = 0; i < MAX_BUTTONS; i++)
                m_MouseButtons[i] = false;
        }

        Window::~Window()
        {
            glfwTerminate();
        }

        bool Window::init()
        {
            if (!glfwInit())
            {
                std::cout << "Failed to initialize GLFW!" << std::endl;
                return false;
            }

            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
            if (!m_Window)
            {
                std::cout << "Failed to create GLFW window!" << std::endl;
                return false;
            }

            glfwMakeContextCurrent(m_Window);
            glfwSetWindowUserPointer(m_Window, this);
            glfwSetWindowSizeCallback(m_Window, window_resize);
            glfwSetKeyCallback(m_Window, key_callback);

            if (glewInit() != GLEW_OK) // glewInit needs to be after glfwMakeContextCurrent
            {
                std::cout << "Failed to initialize GLEW!" << std::endl;
                return false;
            }

            std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

            return true;
        }

        bool Window::closed() const
        {
            return glfwWindowShouldClose(m_Window) == 1;
        }

        void Window::update()
        {
            glfwPollEvents();
            glfwSwapBuffers(m_Window);
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        bool Window::isKeyPressed(unsigned int keycode)
        {
            if (keycode >= MAX_KEYS)
                return false;

            return m_Keys[keycode];
        }

        void window_resize(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        };

        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            win->m_Keys[key] = action != GLFW_RELEASE;
        }
    }
}