#include "Embedded.h"

namespace sp
{
	namespace internal
	{
		// internal should not be used in the game API
		byte DEFAULT_FONT_ARRAY[] =
		{
	#include "files/SourceSansPro-Light.embed"
		};

		byte *DEFAULT_FONT = DEFAULT_FONT_ARRAY;
		uint DEFAULT_FONT_SIZE = sizeof(DEFAULT_FONT_ARRAY);
	}
}