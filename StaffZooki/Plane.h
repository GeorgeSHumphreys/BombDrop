#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"

class Plane
{
public:
	Plane(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Plane();

	void Draw();
	void Update();
	void MaterialSetup();

private:
	GLfloat _rotation;
	Vector3 _position;
	Material* _material;
	Vector3 _scale;

	Mesh* _mesh;
	Texture2D* _texture;

	
};

