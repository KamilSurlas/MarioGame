#include "game.h"


Map map(1.0f);
Camera camera(20.0f);
Mario mario;
std::vector<Object*> objects{};
sf::Music music;

void Begin(const sf::Window& window)
{
	LoadResources();

	music.openFromFile("./resources/sounds/music.ogg");
	music.setLoop(true);
	music.setVolume(50);
	
	Physics::Init();

	sf::Image image;
	image.loadFromFile("map.png");
	mario.position = map.CreateFromImage(image,objects);
	mario.Begin();

	for (auto& object : objects)
	{
		object->Begin();
	}
	music.play();
}

void Update(float deltaTime)
{
	Physics::Update(deltaTime);
	mario.Update(deltaTime);
	camera.position = mario.position;

	for (auto& object : objects)
	{
		object->Update(deltaTime);
	}
}

void Render(Renderer& renderer)
{
	renderer.Draw(Resources::textures["sky.png"], camera.position, camera.GetViewSize());

	mario.RenderMario(renderer);
	map.Draw(renderer);

	for (auto& object : objects)
	{
		object->Render(renderer);
	}

	Physics::DebugDraw(renderer);
}

void DeleteObject(Object* obj)
{
	const auto& it = std::find(objects.begin(), objects.end(), obj);
	if (it!=objects.end())
	{
		delete* it;
		objects.erase(it);
	}
}

void LoadResources()
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
	for (auto& file : std::filesystem::directory_iterator("./resources/sounds/"))
	{
		if (file.is_regular_file() &&
			(file.path().extension() == ".wav" || file.path().extension() == ".ogg"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(
				file.path().string());
		}
	}
}

