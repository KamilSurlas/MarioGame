#include "game.h"


Map map(16.0f);
Camera camera(320.0f);
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

	sf::Image image;
	image.loadFromFile("map.png");
	mario.position = map.CreateFromImage(image);
	
	
}

void Update(float deltaTime)
{
	mario.Update(deltaTime);
	camera.position = mario.position;
}

void Render(Renderer& renderer)
{
	mario.RenderMario(renderer);
	map.Draw(renderer);
}

