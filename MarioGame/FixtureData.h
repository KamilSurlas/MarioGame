#pragma once
#include "Physics.h"
class Mario;
class Object;
class CollisionListenerHelper;
enum class FixtureDataType
{
	MapTile,
	Object,
	Mario
};

struct FixtureData
{
	FixtureDataType type{};
	CollisionListenerHelper* listener{};
	union
	{
		Mario* mario;
		Object* object;
		struct { int mapX, mapY; };
	};
};