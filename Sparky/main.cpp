// #include <iostream>
// #include <vector>
#include <GL/glew.h>

#if 1
#include "src/graphics/shader.h"
#include "src/graphics/window.h"
#include "src/maths/maths.h"
// timer.h needs to come before FreeImage, which is inside batchrenderer2d.h
// timer uses LARGE_INTEGER, which uses DWORD, which FreeImage overrides
#include "src/utils/timer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/sprite.h"

#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/label.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader *s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader &shader = *s;
	shader.enable();
	shader.setUniform("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	// PNG needs to be saved without background, 8 bit per channel (RGB)
	Texture *textures[] = { new Texture("test.png"), new Texture("test2.png"),
						   new Texture("test3.png") };

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	Group *g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label *fps = new Label("", 0.4f, 0.4f, maths::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	g->add(new Sprite(0, 0, 6.0f, 1.5f, maths::vec4(0.3f, 0.3f, 0.3f, 0.9f)));
	g->add(fps);
	layer.add(g);

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	shader.enable();
	shader.setUniform("textures", texIDs, 10);
	shader.setUniform(
		"pr_matrix", mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	double x, y;

	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		window.getMousePosition(x, y);
		shader.setUniform("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f),
			(float)(9.0f - y * 18.0f / 540.0f)));
		layer.render();

		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;

			std::cout << window.getWidth() << "," << window.getHeight() << std::endl;
		}
	}

	for (Texture *tex : textures)
	{
		delete tex;
	};
	return 0;
}
#else
int main()
{
	const char *filename = "test.png";

	// image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	// pointer to the image, once loaded
	FIBITMAP *dib(0);
	// pointer to the image data
	BYTE *bits(0);
	// image width and height
	unsigned int width(0), height(0);
	// OpenGL's image ID to map to
	GLuint gl_texID;

	// check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	// if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	// if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	// check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	// if the image failed to load, return failure
	if (!dib)
		return false;

	// retrieve the image data
	bits = FreeImage_GetBits(dib);
	// get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	// if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	std::cout << width << ", " << height << std::endl;

	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);

	// prints the colors Bottom to Top, Left to Right
	unsigned int pitch = FreeImage_GetPitch(dib);
	for (int y = 0; y < height; y++)
	{
		BYTE *pixel = (BYTE *)bits;
		for (int x = 0; x < width; x++)
		{
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " "
				<< +pixel[FI_RGBA_BLUE] << " " << std::endl;
			pixel += 3;
		}
		bits += pitch;
	}

	////if this texture ID is in use, unload the current texture
	// if (m_texID.find(texID) != m_texID.end())
	//     glDeleteTextures(1, &(m_texID[texID]));

	////generate an OpenGL texture ID for this texture
	// glGenTextures(1, &gl_texID);
	////store the texture ID mapping
	// m_texID[texID] = gl_texID;
	////bind to the new texture ID
	// glBindTexture(GL_TEXTURE_2D, gl_texID);
	////store the texture data for OpenGL use
	// glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
	//     border, image_format, GL_UNSIGNED_BYTE, bits);

	////Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	return 0;
}
#endif