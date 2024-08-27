#include "CollisionListener.h"

void CollisionListener::BeginContact(b2Contact* contact)
{
	CollisionListenerHelper* listener = (CollisionListenerHelper*)contact->GetFixtureA()->GetUserData();

	if (listener)
	listener->OnBeginContact();

	listener = (CollisionListenerHelper*)contact->GetFixtureB()->GetUserData();

	if(listener)
	listener->OnBeginContact();
}

void CollisionListener::EndContact(b2Contact* contact)
{
	CollisionListenerHelper* listener = (CollisionListenerHelper*)contact->GetFixtureA()->GetUserData();

	if (listener)
	listener->OnEndContact();

	listener = (CollisionListenerHelper*)contact->GetFixtureB()->GetUserData();

	if (listener)
	listener->OnEndContact();
}
