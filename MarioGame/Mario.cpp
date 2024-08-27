#include "Mario.h"

const float movementSpeed = 7.0f;
const float jumpVelocity = 4.0f;
void Mario::Begin()
{
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2PolygonShape polygonShape{};

	polygonShape.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef{};
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	b2CircleShape circleShape{};
	circleShape.m_radius = 0.5f;
	circleShape.m_p.Set(0.0f, -0.5f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);

	circleShape.m_p.Set(0.0f, 0.5f);
	fixtureDef.userData = (void*)this;
	body->CreateFixture(&fixtureDef);
}
void Mario::Update(float deltaTime)
{
	float move = movementSpeed;
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
	}
	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
}

void Mario::RenderMario(Renderer& renderer)
{
	renderer.Draw(Resources::textures["mario.png"], position, sf::Vector2f(1.0f,2.0f), angle);
}

void Mario::OnBeginContact()
{
	isOnGround = true;
}

void Mario::OnEndContact()
{
	isOnGround = false;
}
