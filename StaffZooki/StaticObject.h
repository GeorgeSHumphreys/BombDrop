#pragma once
#include "SceneObject.h"
class StaticObject : public SceneObject
{
private:
	GLfloat _rotation;
	Vector3 _position;

public:
	StaticObject(Mesh* mesh, float x, float y, float z);
	~StaticObject();

	void Draw();
	void Update();
};

