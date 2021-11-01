#include "Collisions.h"
#include <iostream>

Collisions* Collisions::instance = nullptr;
// Singleton class


Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!instance)
	{
		instance = new Collisions;
	}

	return instance;
}


bool Collisions::Sphere(SphereCollisionInfo s1, SphereCollisionInfo s2)
{
	// Compare the two radius and actual distance, if dist < both radius = colliding
	float distance = ((s1.position.x - s2.position.x) * (s1.position.x - s2.position.x))
		+ ((s1.position.y - s2.position.y) * (s1.position.y - s2.position.y))
		+ ((s1.position.z - s2.position.z) * (s1.position.z - s2.position.z));

	float radiusDistance = pow(s1.radius + s2.radius, 2);

	if (distance < radiusDistance)
	{
		return true;
	}
	return false;
}