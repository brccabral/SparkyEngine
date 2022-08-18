// Need to install OpenAL https://openal.org/ , use Windows Installer https://openal.org/downloads/
// it will install OpenAL32.dll into System32 and SysWow64

#include <GL/glew.h>

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

#include "src/graphics/font_manager.h"
#include "src/audio/sound_manager.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;
	using namespace audio;

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
			int r = rand() % 256;
			int col = 0xffff00 << 8 | r;

			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	Group *g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label *fps = new Label("", 0.4f, 0.4f, 0xffffffff);
	g->add(new Sprite(0, 0, 6.0f, 1.5f, 0x505050dd));
	g->add(fps);
	layer.add(g);

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	shader.enable();
	shader.setUniform("textures", texIDs, 10);
	shader.setUniform(
		"pr_matrix", mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	SoundManager::add(new Sound("Evacuate", "Evacuate.wav"));
	SoundManager::add(new Sound("BomDia", "BomDia.wav"));

	double x, y;

	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;
	float t = 0.0f;
	while (!window.closed())
	{
		window.clear();
		window.getMousePosition(x, y);
		shader.setUniform("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f),
			(float)(9.0f - y * 18.0f / window.getHeight())));
		layer.render();

		t += 0.001f;
		const std::vector<Renderable2D *> &rs = layer.getRenderables();
		for (unsigned int i = 0; i < rs.size(); i++)
		{
			float c = sin(t) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}

		if (window.isKeyTyped(GLFW_KEY_P))
			SoundManager::get("BomDia")->loop();

		if (window.isKeyTyped(GLFW_KEY_UP))
			SoundManager::get("BomDia")->setGain(SoundManager::get("BomDia")->getGain() + 0.05f);

		if (window.isKeyTyped(GLFW_KEY_DOWN))
			SoundManager::get("BomDia")->setGain(SoundManager::get("BomDia")->getGain() - 0.05f);

		SoundManager::update();
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	for (Texture *tex : textures)
	{
		delete tex;
	};

	return 0;
}
