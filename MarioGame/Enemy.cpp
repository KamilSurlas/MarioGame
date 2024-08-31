#include "Enemy.h"

void Enemy::Begin()
{
	animation = Animation(0.5f,
		{
			AnimFrame(0.25f, Resources::textures["enemy2.png"]),
			AnimFrame(0.00f, Resources::textures["enemy1.png"])
		});
	tag = "enemy";
	fixtureData = new FixtureData();
	fixtureData->object = this;
	fixtureData->type = FixtureDataType::Object;
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2CircleShape circleShape{};
	circleShape.m_radius = 0.5f;

	b2FixtureDef fixtureDef{};
	fixtureDef.userData = fixtureData;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	body->CreateFixture(&fixtureDef);
}

void Enemy::Update(float deltaTime)
{
	if (isDead)
	{
		destroyTimer += deltaTime;
		if (destroyTimer >= 2.0f)
		{
			DeleteObject(this);
		}

		return;
	}
	animation.Update(deltaTime);
	b2Vec2 velocity = body->GetLinearVelocity();

	if (std::abs(velocity.x) <= 0.02f)
	{
		movement *= -1.0f;
	}

	velocity.x = movement;

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
		
}

void Enemy::Render(Renderer& renderer)
{
	renderer.Draw(animation.GetTexture(),!isDead ? position : sf::Vector2f(position.x , position.y + 0.45f),
		sf::Vector2f(1.0f, isDead ? 0.1f : 1.0f), angle);
}

void Enemy::Die()
{
	if (isDead)
		return;

	isDead = true;
}

Enemy::~Enemy()
{
	Physics::world->DestroyBody(body);
	if (fixtureData)
	{
		delete fixtureData;
	}
}

bool Enemy::GetIsDead()
{
	return isDead;
}
