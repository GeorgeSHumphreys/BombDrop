#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h";
#include "SceneObject.h"
#include "StaticObject.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "Creature.h"
#include "PlayerDiamond.h"
#include "PlayerDiamond2.h"
#include "PickupObject.h"
#include "Collisions.h"
#include "HUDImage.h"
#include "ChargeBar.h"
#include "Bomb.h"
#include "Skybox.h"
#include "MeshManager.h"

#define REFRESHRATE 16



class HelloGL
{
public:
	// constructor definition
	HelloGL(int argc, char* argv[]);

	// destructor
	~HelloGL(void);

	void InitObjects();
	void InitLighting();
	void InitGL(int argc, char* argv[]);
	void ResetToMenu();

	void Display();
	void Set2D();
	void Set3D();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void mouse_callback(int x, int y);

	void DisplayString(const char* text, Vector3* position, Color* color);

private:
	void UpdateBombs(float deltaTime);
	void UpdatePickups(float deltaTime);
	void CreateBomb(Vector3* position);
	void DisplayHealth();

	Camera* camera;
	Skybox* _skybox;

	Vector4* _lightPosition;
	Lighting* _lightData;

	SceneObject* _plane;
	SceneObject* _lava;
	Creature* _creatures[2];
	PlayerDiamond* _playerDiamond;
	PlayerDiamond2* _playerDiamond2;

	std::vector<PickupObject*> _coins;
	PickupObject* _gunpowder;

	// Menu and HUD
	bool _menu;
	HUDImage* _HudImage;

	// HUDIMAGES FOR INGAME
	HUDImage* _coinDisplay;
	int _p1Score;
	Vector3 _chargePos[2];
	HUDImage* _IngameHUD;
	HUDImage* _heartDisplay;
	HUDImage* _winnerDisplay;

	// Bomb Test
	std::vector<Bomb*> _bombs;
	float _bombCurrentRate;
	float _bombSpawnRate;

	// Textures and Meshes
	// Load the Mesh's we need
	MeshManager* _meshManager;

	// End Game Screen
	bool _endScreen;
	Creature* _winningCreature;
	float _endGameWait;

	Color _colorWhite;
	float _oldT;
};

