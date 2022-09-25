#pragma once

#include <string>
#include <FreeImage.h>
#include <FreeImage/Utilities.h>
#include <sp/utils/Log.h> // needs to be before GL, redefinition of APIENTRY
#include <sp/Types.h>

namespace sp
{
	SP_API byte *load_image(const char *filename, uint *width, uint *height, uint *bits);
}