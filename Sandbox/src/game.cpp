#include <sparky.h>
#include <app/Application.h>

using namespace sparky;
using namespace graphics;
using namespace maths;

class Game : public Application
{
private:
	Layer *layer = nullptr;
	Label *fps = nullptr;
	Sprite *sprite = nullptr;
	Shader *shader = nullptr;
	Mask *mask = nullptr;
	Label *debugInfo = nullptr;
	std::string currentSound = "BomDia";
public:
	Game()
		: Application("Test Game", 1280, 720)
	{
	}

	~Game()
	{
		delete layer;
	}

	void Init() override
	{
		Application::Init();
		//window->SetVsync(false);

		FontManager::Get()->SetScale(window->GetWidth() / 32.0f, window->GetHeight() / 18.0f);

		shader = ShaderFactory::DefaultShader();
		//shader = ShaderFactory::BasicLightShader();

		// the orthographic matrix makes the center of the window to be 0,0
		// so, the window is x = [-16 to 16] left to right and y = [-9 to 9] bottom to top
		layer = new Layer(new BatchRenderer2D(tvec2<uint>(1280, 720)), shader, mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->Add(new Sprite(-16.0f, -9.0f, 32, 18, 0xffff00ff)); // add a colored square to screen
		layer->Add(new Sprite(0.0f, 0.0f, 4, 4, 0xffffffff)); // add a colored square to screen

		sprite = new Sprite(6.0f, 3.0f, 4, 4, new Texture("Tex", "res/test.png"));
		layer->Add(sprite); // add a image to screen

		fps = new Label("", -15.5f, 8.0f, 0xffffffff);
		layer->Add(fps); // add a Label object

		debugInfo = new Label("", -15.5f, 6.8f, 0xffffffff);
		layer->Add(debugInfo);

		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		mask = new Mask(new Texture("Mask", "res/mask2.png"));
		mask->transform = mat4::Translate(vec3(-16.0f, -9.0f, 0.0f)) * mat4::Scale(vec3(32, 18, 1));
		layer->SetMask(mask);

		audio::SoundManager::Add(new audio::Sound(currentSound, "res/BomDia.ogg"))->Play();
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

		tvec2<uint> size = ((BatchRenderer2D *)layer->renderer)->GetViewportSize();

		if (window->IsKeyPressed(GLFW_KEY_UP))
		{
			size.x += 16;
			size.y += 9;
		}
		else if (window->IsKeyPressed(GLFW_KEY_DOWN))
		{
			size.x -= 16;
			size.y -= 9;
		}

		if (size.x > 10000)
			size.x = 0;
		if (size.y > 10000)
			size.y = 0;

		debugInfo->text = std::to_string(size.x) + ", " + std::to_string(size.y);
		((BatchRenderer2D *)layer->renderer)->SetViewportSize(size);
		((BatchRenderer2D *)layer->renderer)->SetScreenSize(tvec2<uint>(window->GetWidth(), window->GetHeight()));
	}
};

int main()
{
	Game game;
	game.Start();
	return 0;
}