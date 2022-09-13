#include <sparky.h>
#include <app/Application.h>

using namespace sparky;
using namespace graphics;
using namespace maths;

#define WIDTH 1280
#define HEIGHT 720

class Game : public Application
{
private:
	Layer *layer = nullptr;
	Label *fps = nullptr;
	Sprite *sprite = nullptr;
	Shader *shader = nullptr;
	Mask *mask = nullptr;
	Label **debugInfo = nullptr;
	std::string currentSound = "BomDia";
public:
	Game()
		: Application("Test Game", WIDTH, HEIGHT)
	{}

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
		layer = new Layer(new BatchRenderer2D(tvec2<uint>(WIDTH, HEIGHT)), shader, mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		layer->renderer->SetRenderTarget(RenderTarget::BUFFER);
		// currently this post fx applies a Blur to our screen
		layer->renderer->AddPostEffectsPass(new PostEffectsPass(Shader::FromFile("shaders/postfx.vert", "shaders/postfx.frag")));
		layer->renderer->SetPostEffects(true);

		Texture::SetFilter(TextureFilter::NEAREST);
		sprite = new Sprite(6.0f, 3.0f, 4, 4, new Texture("Tex", "res/test.png"));
		layer->Add(sprite); // add a image to screen

		layer->Add(new Sprite(0.0f, 0.0f, 4, 4, 0xffffffff)); // add a colored square to screen

		fps = new Label("", -15.5f, 8.0f, 0xffffffff);
		layer->Add(fps); // add a Label object

		debugInfo = new Label * [10];
		debugInfo[0] = new Label("", -15.5f, 6.8f, 0xffffffff);
		debugInfo[1] = new Label("", -15.5f, 5.8f, 0xffffffff);
		layer->Add(debugInfo[0]);
		layer->Add(debugInfo[1]);

		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		mask = new Mask(new Texture("Mask", "res/mask2.png"));
		mask->transform = mat4::Translate(vec3(-16.0f, -9.0f, 0.0f)) * mat4::Scale(vec3(32, 18, 1));
		//layer->SetMask(mask);

		// without GLFW the order to display on screen changes
		layer->Add(new Sprite(-16.0f, -9.0f, 32, 18, 0xffff00ff)); // add a colored square to screen
		audio::SoundManager::Add(new audio::Sound(currentSound, "res/BomDia.ogg"))->Play();
	}

	void Tick() override
	{
		fps->text = std::to_string(GetFPS()) + " fps";
		//SPARKY_INFO(GetUPS(), " ups, ", GetFPS(), " fps");
		SPARKY_INFO(window->GetMousePosition());
	}

	void Render() override
	{
		layer->Render();
	}

	void Update() override
	{
		if (window->IsKeyTyped(VK_T))
			layer->renderer->SetRenderTarget(layer->renderer->GetRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
		if (window->IsKeyTyped(VK_P))
			layer->renderer->SetPostEffects(!layer->renderer->GetPostEffects());

		debugInfo[0]->text = std::string("Target: ") + (layer->renderer->GetRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer");
		debugInfo[1]->text = std::string("PostFX: ") + (layer->renderer->GetPostEffects() ? "On" : "Off");
	}
};

int main()
{
	Game game;
	game.Start();
	return 0;
}