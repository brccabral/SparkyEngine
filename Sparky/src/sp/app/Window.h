#pragma once

#include "sp/sp.h"
#include "sp/graphics/FontManager.h"
#include "sp/audio/SoundManager.h"
#include "sp/maths/vec2.h"
#include "sp/graphics/TextureManager.h"

#include "sp/events/Events.h"
#include "sp/app/Input.h"

namespace sp
{

	typedef std::function<void(events::Event &event)> WindowEventCallback;

	class SP_API Window
	{
	private:
		int m_Width, m_Height;
		const char *m_Title;
		bool m_Closed;
		void *m_Handle;

		InputManager *m_InputManager;
		static std::map<void *, Window *> s_Handles;
		bool m_Vsync;

		WindowEventCallback m_EventCallback;

	public:
		Window(const char *title, uint width, uint height);
		~Window();
		void Update();
		void Clear() const;
		bool Closed() const;
		inline InputManager *GetInputManager() const { return m_InputManager; }

		inline uint GetWidth() const { return m_Width; };
		inline uint GetHeight() const { return m_Height; };

		void SetVsync(bool enabled);
		inline bool IsVsync() const { return m_Vsync; }

		void SetEventCallback(const WindowEventCallback &callback);
	private:
		bool Init();

		bool PlatformInit();
		void PlatformUpdate();

		// Window event callbacks (TODO: more platform independent)
		friend void ResizeCallback(Window *window, int width, int height);
		friend void FocusCallback(Window *window, bool focused);
	public:
		static void RegisterWindowClass(void *handle, Window *window);
		static Window *GetWindowClass(void *handle);
	};

}
