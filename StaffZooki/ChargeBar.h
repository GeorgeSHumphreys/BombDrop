#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"

class ChargeBar
{
public:
	ChargeBar(float x, float y, float z);
	~ChargeBar();

	void Draw();
	void Update(float deltaTime);
	float GetCharge() { return _chargePercent; };
	void SetCharge(float charge) { _chargePercent = charge; };

private:
	// Position Setup
	Vector3 _position;

	// Charge variables
	float _chargePercent;
	float _chargeRate;
	float _barLength;
};

