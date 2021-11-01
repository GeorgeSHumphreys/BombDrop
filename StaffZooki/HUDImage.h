#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Texture2D.h"
#include <iostream>

class HUDImage
{
public:
	HUDImage(std::string path, float x, float y, float z, float sx = 1, float sy = 1, float sz = 1);
	~HUDImage();

	void Update(float deltaTime);
	void Draw();
private:
	Texture2D* _texture;
	Rotation _rotation;
	Vector3 _position;
	Vector3 _scale;

	float xBounds, yBounds;
};

