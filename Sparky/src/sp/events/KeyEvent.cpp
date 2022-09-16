#include "KeyEvent.h"

namespace sparky
{
	namespace events
	{

		KeyEvent::KeyEvent(int keyCode, Event::Type type)
			: Event(type), m_KeyCode(keyCode)
		{}

		KeyPressedEvent::KeyPressedEvent(int button, int repeat)
			: KeyEvent(button, Event::Type::KEY_PRESSED), m_Repeat(0)
		{}

		KeyReleasedEvent::KeyReleasedEvent(int button)
			: KeyEvent(button, Event::Type::KEY_RELEASED)
		{}

	}
}