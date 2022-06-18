#pragma once

#include <GLFW/glfw3.h>

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

        public:
            Window(const char* title, int width, int height);
            ~Window();
            void update() const;
            bool closed() const;

        private:
            bool init();
        };
    }
}