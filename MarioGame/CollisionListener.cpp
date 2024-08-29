#include "CollisionListener.h"

void CollisionListener::BeginContact(b2Contact* contact)
{
	FixtureData* data = (FixtureData*)contact->GetFixtureA()->GetUserData();

	if (data && data->listener)
		data->listener->OnBeginContact(contact->GetFixtureB());

	data = (FixtureData*)contact->GetFixtureB()->GetUserData();

	if (data && data->listener)
		data->listener->OnBeginContact(contact->GetFixtureA());
}

void CollisionListener::EndContact(b2Contact* contact)
{
	FixtureData* data = (FixtureData*)contact->GetFixtureA()->GetUserData();

	if (data && data->listener)
		data->listener->OnEndContact(contact->GetFixtureB());

	data = (FixtureData*)contact->GetFixtureB()->GetUserData();

	if (data && data->listener)
		data->listener->OnEndContact(contact->GetFixtureA());
}
