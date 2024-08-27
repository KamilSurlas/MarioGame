#include "game.h"


Map map(1.0f);
Camera camera(20.0f);
Mario mario;


void Begin(const sf::Window& window)
{
	for (auto& file : std::filesystem::directory_iterator("./resources/textures/"))
	{
		if (file.is_regular_file() &&
			(file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(
				file.path().string());			
		}
	}

	Physics::Init();

	sf::Image image;
	image.loadFromFile("map.png");
	mario.position = map.CreateFromImage(image);
	mario.Begin();
	
}

void Update(float deltaTime)
{
	Physics::Update(deltaTime);
	mario.Update(deltaTime);
	camera.position = mario.position;
}

void Render(Renderer& renderer)
{
	mario.RenderMario(renderer);
	map.Draw(renderer);

	Physics::DebugDraw(renderer);
}

