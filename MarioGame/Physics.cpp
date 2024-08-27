#include "Physics.h"

b2World Physics::world{b2Vec2(0.0f, 10.0f)};
MyDebugDraw* Physics::debugDraw{};


void Physics::Init()
{
}

void Physics::Update(float deltaTime)
{
	world.Step(deltaTime, 6, 2);
	static CollisionListener collisionListener;
	world.SetContactListener(&collisionListener);
}

void Physics::DebugDraw(Renderer& renderer)
{
	if (!debugDraw)
	{
		debugDraw = new MyDebugDraw(renderer.target);
		debugDraw->SetFlags(b2Draw::e_aabbBit);
		world.SetDebugDraw(debugDraw);
	}

	world.DrawDebugData();
}
