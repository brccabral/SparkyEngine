#if 1
#include "../src/sparky.h"

using namespace sparky;
using namespace graphics;
using namespace maths;

class Game : public Sparky
{
private:
	Window *window;
	Layer *layer;
	Label *fps;
public:
	Game()
		:window(nullptr), layer(nullptr), fps(nullptr)
	{

	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		// the orthographic matrix makes the center of the window to be 0,0
		// so, the window is x = [-16 to 16] left to right and y = [-9 to 9] bottom to top
		layer = new Layer(new BatchRenderer2D(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->add(new Sprite(0.0f, 0.0f, 4, 4, 0xffffffff));
		layer->add(new Sprite(6.0f, 3.0f, 4, 4, new Texture("test.png")));

		fps = new Label("", -15.5f, 8.0f, 0xffffffff);
		layer->add(fps);
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
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
#endif