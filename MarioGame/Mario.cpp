#include "Mario.h"
#include <iostream>
#include "game.h"
#include "Enemy.h"

const float movementSpeed = 7.0f;
const float jumpVelocity = 4.0f;
void Mario::Begin()
{
	runAnimation = Animation(0.55f,
		{
			AnimFrame(0.30f,Resources::textures["run3.png"]),
			AnimFrame(0.15f,Resources::textures["run2.png"]),
			AnimFrame(0.10f,Resources::textures["run1.png"])
		});

	jumpSound.setBuffer(Resources::sounds["jump.wav"]);
	jumpSound.setVolume(70);

	fixtureData.listener = this;
	fixtureData.mario = this;
	fixtureData.type = FixtureDataType::Mario;
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);
	b2FixtureDef fixtureDef{};
	fixtureDef.userData = (void*)&fixtureData;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	b2CircleShape circleShape{};
	circleShape.m_radius = 0.5f;
	circleShape.m_p.Set(0.0f, -0.5f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);
	circleShape.m_p.Set(0.0f, 0.5f);
	body->CreateFixture(&fixtureDef);
	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(0.5f, 0.5f);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
	polygonShape.SetAsBox(0.4f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
	fixtureDef.isSensor = true;
	groundDetection = body->CreateFixture(&fixtureDef);
}
void Mario::Update(float deltaTime)
{
	float move = movementSpeed;
	runAnimation.Update(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		move *= 2;
	}

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isOnGround)
	{
		velocity.y -= jumpVelocity;
		jumpSound.play();
	}
	textureToDraw = runAnimation.GetTexture();
	if (velocity.x < -0.02f)
	{
		facingLeft = true;
	}
	else if (velocity.x > 0.02f) 
	{
		facingLeft = false;
	}
	else
	{
		textureToDraw = Resources::textures["mario.png"];
	}
	
	if (!isOnGround)
	{
		textureToDraw = Resources::textures["jump.png"];
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
}

void Mario::RenderMario(Renderer& renderer)
{
	renderer.Draw(textureToDraw,
		position, sf::Vector2f(facingLeft? -1.0f:1.0f,2.0f), angle);
}

void Mario::OnBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData();
	if (!data)
	{
		return;
	}
	if (groundDetection == self && data->type == FixtureDataType::MapTile)
	{
		isOnGround++;
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "coin") {
		DeleteObject(data->object);
		std::cout << "coins = " << ++coins << "\n";
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "enemy") 
	{
		Enemy* enemy = dynamic_cast<Enemy*>(data->object);
		if (!enemy)
		{
			return;
		}
		if (groundDetection == self)
		{	
			enemy->Die();
		}
		else if (!enemy->GetIsDead())
		{
			isDead = true;
			enemy->Die();
		}
	}
}

void Mario::OnEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData();

	if (!data)
	{
		return;
	}

	if (groundDetection == self && data->type == FixtureDataType::MapTile && isOnGround > 0)
	{
		isOnGround--;
	}
}

size_t Mario::GetMarioCoins()
{
	return coins;
}
