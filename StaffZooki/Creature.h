#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"
#include "PlayerDiamond.h"
#include "ChargeBar.h"

class Creature : public SceneObject
{
private:
	int _mode;

	Vector3* _target;
	Vector3 _direction;

	// Movement
	float _movespeed;
	float _baseMoveSpeed;
	float _fastMoveSpeed;
	float _turnSpeed;
	float _gravity;
	float _vely;
	float _terminal;
	float _targetAngle;

	// Collision
	float _collisionRadius;
	bool _drawCollision;

	// Floating Diamond
	PlayerDiamond* _localDiamond;

	// Bomb Bar
	ChargeBar* _bombCharge;
	bool _bombSpawn;
	bool _trySpawn;

	// Bomb Knockback
	bool _takingKnockback;
	float _knockbackForce;
	Vector3 _knockbackDirection;
	float _knockbackTime;

	// Health
	int _health;
	void GetDirection();
	void MoveFacingDirection(float deltaTime);
public:
	Creature(float x, float y, float z, int mode);
	~Creature();

	void Draw() override;
	void DrawChargeBar() { _bombCharge->Draw(); };
	void Update(float deltaTime);
	void PlayerInput(unsigned char key, int x, int y);
	void PlayerInputRelease(unsigned char key, int x, int y);
	void MaterialSetup() override;


	void TakeKnockback(Vector3 bombPos);
	void SetTargetPointer(Vector3* target) { _target = target; }
	int GetHealth() { return _health; };
	bool CheckForBomb() { return _bombSpawn; };
	void SpawnBomb() { _trySpawn = true; };
	void IncreaseCharge(float charge) { _bombCharge->SetCharge(_bombCharge->GetCharge() + charge); };
	float GetCharge() { return _bombCharge->GetCharge(); };
	void Reset();
	void TakeDamage(int damage) { _health -= damage; };
	Vector3* GetPosPointer() { return &_position; }
	void SetPos(float x, float y, float z);
	SphereCollisionInfo GetSphereCollision() { return SphereCollisionInfo(_collisionRadius, _position); }
};

