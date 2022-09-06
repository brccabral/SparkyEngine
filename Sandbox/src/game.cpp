#if 1
#include <sparky.h>

using namespace sparky;
using namespace graphics;
using namespace maths;

class Game : public Sparky
{
private:
	Window *window;
	Layer *layer;
	Label *fps;
	Sprite *sprite;
	Shader *shader;
	std::string currentSound = "BomDia";
public:
	Game()
		:window(nullptr), layer(nullptr), fps(nullptr), shader(nullptr), sprite(nullptr)
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
	#ifdef SPARKY_EMSCRIPTEN
		shader = new Shader("res/shaders/basic.es3.vert", "res/shaders/basic.es3.frag");
	#else
		shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	#endif
		// the orthographic matrix makes the center of the window to be 0,0
		// so, the window is x = [-16 to 16] left to right and y = [-9 to 9] bottom to top
		layer = new Layer(new BatchRenderer2D(), shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->add(new Sprite(0.0f, 0.0f, 4, 4, 0xffffffff));
	#ifdef SPARKY_EMSCRIPTEN
		sprite = new Sprite(6.0f, 3.0f, 4, 4, new Texture("Tex", "res/test.png"));
	#else
		sprite = new Sprite(6.0f, 3.0f, 4, 4, new Texture("Tex", "test.png"));
	#endif
		layer->add(sprite);

		fps = new Label("", -15.5f, 8.0f, 0xffffffff);
		layer->add(fps);

	#ifdef SPARKY_EMSCRIPTEN
		// to play  sound on web startup, user need to interact with browser before this function is called
		audio::SoundManager::add(new audio::Sound(currentSound, "res/BomDia.ogg"))->play();
	#else
		audio::SoundManager::add(new audio::Sound(currentSound, "BomDia.ogg"))->play();
	#endif
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		SPARKY_INFO(getUPS(), " ups, ", getFPS(), " fps");
		SPARKY_WARN(getUPS(), " ups, ", getFPS(), " fps");
		SPARKY_ERROR(getUPS(), " ups, ", getFPS(), " fps");
		SPARKY_FATAL(getUPS(), " ups, ", getFPS(), " fps");
		/*SPARKY_INFO("tick %d", 99);
		SPARKY_WARN("tick %d", 88);
		SPARKY_ERROR("tick %d", 77);
		SPARKY_FATAL("tick %d", -1);
		SPARKY_ASSERT(1 == 2, "test");*/
	}

	void render() override
	{
		layer->render();
	}

	void update() override
	{
		float speed = 0.5f;
		if (window->isKeyTyped(GLFW_KEY_UP))
			sprite->position.y += speed;
		if (window->isKeyTyped(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->isKeyTyped(GLFW_KEY_RIGHT))
			sprite->position.x += speed;
		if (window->isKeyTyped(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		if (window->isKeyTyped(GLFW_KEY_P))
			audio::SoundManager::get(currentSound)->play();
		if (window->isKeyTyped(GLFW_KEY_UP))
			audio::SoundManager::get(currentSound)->setGain(audio::SoundManager::get(currentSound)->getGain() + 0.05f);
		if (window->isKeyTyped(GLFW_KEY_DOWN))
			audio::SoundManager::get(currentSound)->setGain(audio::SoundManager::get(currentSound)->getGain() - 0.05f);

		maths::vec2 mouse = window->getMousePosition();
		shader->setUniform("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f),
			(float)(9.0f - mouse.y * 18.0f / window->getHeight())));
	}

};

int main()
{
	Game game;
	game.start();
	return 0;
}
#endif