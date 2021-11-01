#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"
#include "PlayerDiamondBars.h"

class PlayerDiamond : public SceneObject
{
protected:
	PlayerDiamondBars* _barsObject;

	float _movespeed;
	float _baseMoveSpeed;
	float _fastMoveSpeed;

	float _hoverHeight;
	float _hoverTime;
	float _hoverSpeed;

	int _moveVert;
	int _moveHoriz;
public:
	PlayerDiamond(float x, float y, float z, int mode);
	~PlayerDiamond();

	void Draw() override;
	void Update(float deltaTime);
	void MaterialSetup() override;
	virtual void PlayerInput(unsigned char key, int x, int y);
	virtual void PlayerInputRelease(unsigned char key, int x, int y);

	void SetPos(float x, float y, float z);
	Vector3* GetPosPointer() { return &_position; }
};

