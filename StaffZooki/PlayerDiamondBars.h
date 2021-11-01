#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Structures.h"

class PlayerDiamondBars : public SceneObject
{
public:
	PlayerDiamondBars(float x, float y, float z);
	~PlayerDiamondBars();

	void Update(float deltaTime);
	void MaterialSetup() override;

private:

};

