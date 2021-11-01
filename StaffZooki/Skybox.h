#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"
class Skybox : public SceneObject
{
public:
	Skybox(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Skybox();

	void Update();
	void MaterialSetup() override;

private:

};

