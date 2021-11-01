#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
class Camera
{
public:
	Camera();
	~Camera();
	void CameraUpdate(int x, int y);
	void Update(float deltaTime);
	void MoveFacingDirection(int x);
	void Look();
	void SetTarget(Vector3* position);
	void SetTarget(Vector3* position, Vector3* position2);
	void SetMode(CameraMode mode);
	void SetPos(float x, float y, float z);


private:
	void FindMultiMiddle();

	Vector3 _eye, _center, _up;
	Vector3 _cameraFront;
	Vector3 _direction;

	Vector3* _target;
	Vector3* _target2;

	double _lastX;
	double _lastY;

	float _yaw;
	float _pitch;

	float _menuOffsetx, _menuOffsetz;

	CameraMode _mode;
};

