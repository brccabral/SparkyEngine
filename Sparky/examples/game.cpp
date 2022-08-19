#include "../src/sparky.h"

using namespace sparky;
using namespace graphics;
using namespace maths;

class Game : public Sparky
{
private:
	Window *window;
	Layer *layer;
public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		layer = new Layer(new BatchRenderer2D(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->add(new Sprite(0.0f, 0.0f, 4, 4, 0xffffffff));
	}

	void render() override
	{
		layer->render();
	}

};

int main()
{
	Game game;
	game.start();
	return 0;
}