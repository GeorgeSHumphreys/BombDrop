#include "Camera.h"
#include <math.h>
#include <iostream>
#include "MathFuncs.h"


Camera::Camera()
{
	// Camera Setup
	_eye.x = -57.0f; _eye.y = 72.0f; _eye.z = 36.0f;
	_center.x = 0.0f; _center.y = 0.0f; _center.z = 0.0f;
	_up.x = 0.0f; _up.y = 1.0f; _up.z = 0.0f;

	_cameraFront.x = 0;
	_cameraFront.y = 0;
	_cameraFront.z = 0;

	_lastX = 400;
	_lastY = 400;
	_pitch = -70;
	_yaw = 0;


	_direction.x = -sin((_yaw * (3.1419 / 180)));
	_direction.y = sin((_pitch * (3.1419 / 180)));
	_direction.z = -cos(_yaw * (3.1419 / 180)) * cos(_pitch * (3.1419 / 180));

	Vector3 output = MathFuncs::Normalise(_direction.x, _direction.y, _direction.z);
	_cameraFront = output;

	_mode = CONTROL;
	_target = nullptr;
	_target2 = nullptr;

	_menuOffsetx = 0;
	_menuOffsetz = 0;
}

Camera::~Camera()
{

}

void Camera::Look()
{
	// Mode selection setting up needed LookAts
	if (_mode == TARGET)
	{
		if (_target != nullptr)
		{
			gluLookAt(_eye.x, _eye.y, _eye.z, _target->x, _target->y, _target->z, _up.x, _up.y, _up.z);
		}
		else
		{
			_mode = CONTROL;
		}
	}
	else if (_mode == MENU)
	{
		gluLookAt(_eye.x + _menuOffsetx, _eye.y, _eye.z - _menuOffsetz, _target->x, _target->y, _target->z, _up.x, _up.y, _up.z);
	}
	else if (_mode == CONTROL)
	{
		gluLookAt(_eye.x, _eye.y, _eye.z, _eye.x + _cameraFront.x, _eye.y + _cameraFront.y, _eye.z + _cameraFront.z, _up.x, _up.y, _up.z);
	}
	else if (_mode == MULTITARGET)
	{
		FindMultiMiddle();
	}
}

void Camera::FindMultiMiddle()
{
	Vector3 center;

	if (_target != nullptr && _target2 != nullptr)
	{
		float xDist, yDist, zDist, xCamDist, yCamDist, zCamDist;
		// Find center between the 2 targets to look at
		xDist = _target2->x - _target->x;
		yDist = _target2->y - _target->y;
		zDist = _target2->z - _target->z;

		// Set the Target
		center.y = _target->y;
		center.x = _target->x + xDist / 2;
		center.z = _target->z + zDist / 2;

		// DISTANCE FROM CAMERA TO NEW POINT
		xCamDist = center.x - -67;
		yCamDist = center.y - 66;
		zCamDist = center.z - -4.2;

		// Normalise Data
		_direction = MathFuncs::Normalise(xCamDist, yCamDist, zCamDist);


		// Find the raw length between the 2 targets
		float distLength = sqrt(xDist * xDist + zDist * zDist);

		// Look at that target from the specified position
		gluLookAt(_eye.x, _eye.y, _eye.z, center.x, center.y, center.z, _up.x, _up.y, _up.z);
	}
	else
	{
		_mode = TARGET;
	}
}

void Camera::SetMode(CameraMode mode)
{
	_mode = mode;

	if (_mode == MULTITARGET)
	{
		_eye.x = -67.7646;
		_eye.y = 66.94;
		_eye.z = -4.2;
	}
}

void Camera::SetTarget(Vector3* position)
{
	_target = position;
}

void Camera::SetTarget(Vector3* position, Vector3* position2)
{
	_target = position;
	_target2 = position2;
}

void Camera::SetPos(float x, float y, float z)
{
	_eye.x = x;
	_eye.y = y;
	_eye.z = z;
}

void Camera::Update(float deltaTime)
{
	if (_mode == MENU)
	{
		// Each if statement applies to each "Corner" creating the square movement
		if (_menuOffsetx < 100 && _menuOffsetz <= 0)
		{
			_menuOffsetx = _menuOffsetx + 10 * deltaTime;
		}
		else if(_menuOffsetz < 100 && _menuOffsetx >= 100)
		{
			_menuOffsetz = _menuOffsetz + 10 * deltaTime;
		}

		if (_menuOffsetz >= 100 && _menuOffsetx > 0)
		{
			_menuOffsetx = _menuOffsetx - 10 * deltaTime;
		}
		else if (_menuOffsetz > 0 && _menuOffsetx <= 0)
		{
			_menuOffsetz = _menuOffsetz - 10 * deltaTime;
		}
	}
	
}

void Camera::CameraUpdate(int x, int y)
{

	if (_mode == CONTROL)
	{
		// Find Mouse diff
		float xoffset = x - _lastX;
		float yoffset = _lastY - y;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		_yaw -= xoffset;
		_pitch += yoffset;

		// Add boundaries
		if (_pitch > 70.0f) _pitch = 70.0f;
		if (_pitch < -60.0f) _pitch = -60.0f;

		// Calculate vector direction
		_direction.x = -sin((_yaw * (3.1419 / 180)));
		_direction.y = sin((_pitch * (3.1419 / 180)));
		_direction.z = -cos(_yaw * (3.1419 / 180)) * cos(_pitch * (3.1419 / 180));

		Vector3 output = MathFuncs::Normalise(_direction.x, _direction.y, _direction.z);
		// Apply to camera forward
		_cameraFront = output;

		glutWarpPointer(400, 400);
	}
}

void Camera::MoveFacingDirection(int x)
{
	// If passed a 1, goes forwards, if passed a 0, goes backwards
	_eye.x += _direction.x * x;
	_eye.y += _direction.y * x;
	_eye.z += _direction.z * x;
}