#include "Physics.h"
#include "CollisionListener.h"

b2World* Physics::world{};
MyDebugDraw* Physics::debugDraw{};

Physics::~Physics()
{
	delete debugDraw;
	debugDraw = nullptr;
}

void Physics::Init()
{
	if (world)
		delete world;

	world = new b2World(b2Vec2(0.0f, 10.0f));
	world->SetDebugDraw(debugDraw);
}

void Physics::Update(float deltaTime)
{
	world->Step(deltaTime, 8, 4);
	static CollisionListener collisionListener;
	world->SetContactListener(&collisionListener);
}

void Physics::DebugDraw(Renderer& renderer)
{
	if (!debugDraw)
	{
		debugDraw = new MyDebugDraw(renderer.target);
		debugDraw->SetFlags(0u);
		world->SetDebugDraw(debugDraw);
	}

	world->DrawDebugData();
}
