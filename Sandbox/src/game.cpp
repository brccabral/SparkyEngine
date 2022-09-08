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
	Mask *mask = nullptr;
	Label *debugInfo;
	std::string currentSound = "BomDia";
public:
	Game()
		:window(nullptr), layer(nullptr), fps(nullptr), shader(nullptr), sprite(nullptr), debugInfo(nullptr)
	{}

	~Game()
	{
		delete layer;
	}

	void Init() override
	{
		window = CreateWindow("Test Game", 1280, 720);
		FontManager::Get()->SetScale(window->GetWidth() / 32.0f, window->GetHeight() / 18.0f);

		shader = ShaderFactory::DefaultShader();
		//shader = ShaderFactory::BasicLightShader();

		// the orthographic matrix makes the center of the window to be 0,0
		// so, the window is x = [-16 to 16] left to right and y = [-9 to 9] bottom to top
		layer = new Layer(new BatchRenderer2D(tvec2<uint>(1280, 720)), shader, mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->Add(new Sprite(-16.0f, -9.0f, 32, 18, 0xffff00ff)); // add a colored square to screen
		layer->Add(new Sprite(0.0f, 0.0f, 4, 4, 0xffffffff)); // add a colored square to screen

	#ifdef SPARKY_PLATFORM_WEB
		sprite = new Sprite(6.0f, 3.0f, 4, 4, new Texture("Tex", "res/test.png"));
	#else
		sprite = new Sprite(6.0f, 3.0f, 4, 4, new Texture("Tex", "res/test.png"));
	#endif
		layer->Add(sprite); // add a image to screen

		fps = new Label("", -15.5f, 8.0f, 0xffffffff);
		layer->Add(fps); // add a Label object

		debugInfo = new Label("", -15.5f, 6.8f, 0xffffffff);
		layer->Add(debugInfo);

		//Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		//mask = new Mask(new Texture("Mask", "res/mask2.png"));
		//layer->SetMask(mask);

		//shader->Bind();
		//shader->SetUniform("mask_matrix", mat4::translation(vec3(200, 0, 0)));


	#ifdef SPARKY_PLATFORM_WEB
		// to play  sound on web startup, user need to interact with browser before this function is called
		audio::SoundManager::Add(new audio::Sound(currentSound, "res/BomDia.ogg"))->Play();
	#else
		audio::SoundManager::Add(new audio::Sound(currentSound, "res/BomDia.ogg"))->Play();
	#endif
	}

	void Tick() override
	{
		fps->text = std::to_string(GetFPS()) + " fps";
		//SPARKY_INFO(GetUPS(), " ups, ", GetFPS(), " fps");
	}

	void Render() override
	{
		layer->Render();
	}

	void Update() override
	{
		if (window->IsKeyPressed(GLFW_KEY_1))
			((BatchRenderer2D *)layer->renderer)->SetRenderTarget(RenderTarget::SCREEN);
		if (window->IsKeyPressed(GLFW_KEY_2))
			((BatchRenderer2D *)layer->renderer)->SetRenderTarget(RenderTarget::BUFFER);

		maths::tvec2<uint> size = ((BatchRenderer2D *)layer->renderer)->GetViewportSize();

		if (window->IsKeyPressed(GLFW_KEY_UP))
		{
			size.x++;
			size.y++;
		}
		else if (window->IsKeyPressed(GLFW_KEY_DOWN))
		{
			size.x--;
			size.y--;
		}
		debugInfo->text = std::to_string(size.x) + ", " + std::to_string(size.y);
		((BatchRenderer2D *)layer->renderer)->SetViewportSize(size);

		/*
		float speed = 0.5f;
		if (window->IsKeyTyped(GLFW_KEY_UP))
			sprite->position.y += speed;
		if (window->IsKeyTyped(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->IsKeyTyped(GLFW_KEY_RIGHT))
			sprite->position.x += speed;
		if (window->IsKeyTyped(GLFW_KEY_LEFT))
			sprite->position.x -= speed;

		static vec3 pos;
		if (window->isKeyPressed(GLFW_KEY_UP))
			pos.y += speed;
		if (window->isKeyPressed(GLFW_KEY_DOWN))
			pos.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_RIGHT))
			pos.x += speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			pos.x -= speed;
		//SPARKY_WARN(pos.x, ", ", pos.y);

		if (mask)
		{
			static vec3 scale((float)mask->texture->getWidth() / (float)mask->texture->getHeight(), 1.0f, 1.0f);
			if (window->isKeyPressed(GLFW_KEY_W))
			{
				scale.y += speed;
				scale.x += speed;
			}
			if (window->isKeyPressed(GLFW_KEY_S))
			{
				scale.y -= speed;
				scale.x -= speed;
			}
			mask->transform = mat4::translation(pos) * mat4::Scale(scale);
		}

		if (window->IsKeyTyped(GLFW_KEY_P))
			audio::SoundManager::get(currentSound)->Play();
		if (window->IsKeyTyped(GLFW_KEY_UP))
			audio::SoundManager::get(currentSound)->SetGain(audio::SoundManager::get(currentSound)->GetGain() + 0.05f);
		if (window->IsKeyTyped(GLFW_KEY_DOWN))
			audio::SoundManager::get(currentSound)->SetGain(audio::SoundManager::get(currentSound)->GetGain() - 0.05f);

		maths::vec2 mouse = window->GetMousePosition();
		shader->setUniform("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f),
			(float)(9.0f - mouse.y * 18.0f / window->getHeight())));
		*/
	}

};

int main()
{
	Game game;
	game.Start();
	return 0;
}
#endif