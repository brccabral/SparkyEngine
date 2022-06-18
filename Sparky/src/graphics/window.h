#pragma once

#include <GL/glew.h> // need to include before GLFW
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace sparky
{
    namespace graphics
    {
        class Window
        {
        private:
            int m_Width, m_Height;
            const char* m_Title;
            GLFWwindow* m_Window;
            bool m_Closed;

            static bool m_Keys[MAX_KEYS];
            static bool m_MouseButtons[MAX_BUTTONS];
            static double m_MouseX, m_MouseY;

        public:
            Window(const char* title, int width, int height);
            ~Window();
            void update();
            void clear() const;
            bool closed() const;

            inline int getWidth() const { return m_Width; };
            inline int getHeight() const { return m_Height; };

            static bool isKeyPressed(unsigned int keycode);

        private:
            bool init();

            // key_callback is friend so it can access private members
            friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        };
    }
}