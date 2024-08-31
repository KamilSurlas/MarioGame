#include "game.h"


Map map(1.0f);
Camera camera(20.0f);
Mario mario;
std::vector<Object*> objects{};
sf::Music music;
sf::Font font{};
sf::Text coinsText("Coins", font);
sf::Text pauseText("Game paused\nPress ESC to back", font);
sf::Text gameOverText("Game over\nPress SPACE to restart or ENTER for exit", font);
bool paused{};

sf::Image image{};
sf::RectangleShape backgroundShape{sf::Vector2f(1.0f,1.0f)};
void Begin(const sf::Window& window)
{
	LoadResources();

	music.openFromFile("./resources/sounds/music.ogg");
	music.setLoop(true);
	music.setVolume(50);
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setOrigin(0.5f, 0.5f);
	

	image.loadFromFile("map.png");
	PrepareGame();
}

void Update(float deltaTime)
{
	if (mario.isDead)
	{
		paused = true;
	}
	if (mario.isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		PrepareGame();
	}
	if (paused)
		return;
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

void RenderUi(Renderer& renderer)
{
	coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
	coinsText.setString("Coins: " + std::to_string(mario.GetMarioCoins()));
	renderer.target.draw(coinsText);
	if (paused)
	{
		backgroundShape.setScale(camera.GetViewSize());
		renderer.target.draw(backgroundShape);
		if (mario.isDead)
		{
			gameOverText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
			renderer.target.draw(gameOverText);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				exit(0);
			}
		}
		else
		{
			pauseText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
			renderer.target.draw(pauseText);
		}
		
	}
}

void DeleteObject(Object* obj)
{
	const auto& it = std::find(objects.begin(), objects.end(), obj);
	if (it!=objects.end())
	{
		delete* it;
		*it = nullptr;
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

	font.loadFromFile("font.ttf");
	coinsText.setFillColor(sf::Color::White);
	coinsText.setOutlineColor(sf::Color::Black);
	coinsText.setOutlineThickness(1.0f);
	coinsText.setScale(0.1f, 0.1f);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(1.0f);
	gameOverText.setScale(0.1f, 0.1f);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(1.0f);
	pauseText.setScale(0.1f, 0.1f);
}

void PrepareGame()
{
	Physics::Init();

	mario = Mario();
	mario.position = map.CreateFromImage(image, objects);

	mario.isDead = false;
	paused = false;

	mario.Begin();
	for (auto& object : objects)
	{
		object->Begin();
	}

	music.play();
}

