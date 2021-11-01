#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"

class PickupObject : public SceneObject
{
public:
	PickupObject(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~PickupObject();

	void Draw() override;
	void Update(float deltaTime);
	void MaterialSetup() override;
	void RandomPosition();


	Vector3* GetPosPointer() { return &_position; }
	SphereCollisionInfo GetSphereCollision() { return SphereCollisionInfo(_collisionRadius, _position); }
private:
	float _rotationSpeed;

	float _collisionRadius;
	bool _drawCollision;

	// Bob up and down
	float _hoverHeight;
	float _hoverTime;
	float _hoverSpeed;
};

