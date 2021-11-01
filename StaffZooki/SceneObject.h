#pragma once
#include "Structures.h"
#include "Texture2D.h"
#include "iostream"
class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;

	Rotation _rotation;
	Vector3 _position;
	Material* _material;
	Vector3 _scale;

public:
	SceneObject(Mesh* mesh, Texture2D* texture, Vector3 position, Rotation rotation, Vector3 scale);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
	virtual void MaterialSetup();
};
