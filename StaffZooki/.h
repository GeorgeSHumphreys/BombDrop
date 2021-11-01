#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"



class Cube : public SceneObject
{
private:
	GLfloat _rotation;
	Vector3 _position;
	Material* _material;

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void MaterialSetup();
};
