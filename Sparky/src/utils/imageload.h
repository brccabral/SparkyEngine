#pragma once

#include <string>
#include <FreeImage.h>
#include <FreeImage/Utilities.h>
#include <GLFW/glfw3.h>

namespace sparky
{
	static BYTE *load_image(const char *filename, GLsizei *width, GLsizei *height, uint *bits)
	{
		// image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		// pointer to the image, once loaded
		FIBITMAP *dib = nullptr;

		// check the file signature and deduce its format
		fif = FreeImage_GetFileType(filename, 0);
		// if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		// if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return nullptr;

		// check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);

		SPARKY_ASSERT(dib, "Could not load image '", filename, "'!");

		// retrieve the image data
		BYTE *pixels = FreeImage_GetBits(dib);
		// get the image width and height
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		*bits = FreeImage_GetBPP(dib);

	#ifdef SPARKY_EMSCRIPTEN
		// Emscripten swaps Red and Blue
		SwapRedBlue32(dib);
	#endif

		int size = *width * *height * (*bits / 8);
		BYTE *result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		return result;
	};
}