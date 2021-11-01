#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"

class Bomb : public SceneObject
{
public:
	Bomb(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Bomb();

	void Update(float deltaTime);
	void Draw() override; // Might be redundant
	void MaterialSetup() override;
	SphereCollisionInfo GetSphereCollision() { return SphereCollisionInfo(_currentRadius, _position); }
	Vector3* GetPosPointer() { return &_position; }
	bool GetExploding() { return _bombTriggered; };
	bool GetDestroyed() { return _destroy; };
	bool GetHitPlayer() { return _hitPlayer; };
	void HitPlayer() { _hitPlayer = true; };
private:
	void SwapMesh();
	// Explosion Variables
	bool _airBomb;
	float _explosionRadius;
	float _currentRadius;
	float _explosionSpeed;
	float _fuseTime;
	bool _bombTriggered;
	float _collisionRadius;
	bool _hitPlayer;
	bool _destroy;
};

