#pragma once
#include "Structures.h"

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();
	bool Sphere(SphereCollisionInfo sphere1, SphereCollisionInfo sphere2);
	//bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();

	static Collisions* instance;
};
