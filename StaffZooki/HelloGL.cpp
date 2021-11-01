#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <time.h>
#include <iostream>
#include <string>


HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL)); // Seed the random
	InitGL(argc, argv); // Initialise opengl
	InitObjects(); // Initialise all the objects
	InitLighting(); // Initialise the Lighting
	glutMainLoop();
}

void HelloGL::InitObjects()
{
	// Load intial time for DeltaTime
	_oldT = glutGet(GLUT_ELAPSED_TIME);

	_meshManager = new MeshManager();

	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Tank.obj"), "Creature");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"TargetDiamond.obj"), "PlayerDiamond");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"DiamondBars.obj"), "DiamondBars");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Gunpowder.obj"), "Gunpowder");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"CoinTest.obj"), "Coin");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Platform.obj"), "Platform");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Bomb.obj"), "Bomb");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Explosion.obj"), "Explosion");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Skybox.obj"), "Skybox");
	_meshManager->AddMesh(MeshLoader::LoadObj((char*)"Plane.obj"), "Lava");


	// Load the Textures
	Texture2D* texture = new Texture2D();
	texture->LoadTextureTGA((char*)"TempTex.tga");
	Texture2D* playerDiamondTex = new Texture2D();
	playerDiamondTex->LoadTextureTGA((char*)"playerDiamondTex.tga");
	Texture2D* playerDiamondTex2 = new Texture2D();
	playerDiamondTex2->LoadTextureTGA((char*)"playerDiamondTex2.tga");
	Texture2D* diamondBarsTex = new Texture2D();
	diamondBarsTex->LoadTextureTGA((char*)"DiamondTex.tga");
	Texture2D* grassTexture = new Texture2D();
	grassTexture->LoadTextureTGA((char*)"Grass.tga");
	Texture2D* tankTexture = new Texture2D();
	tankTexture->LoadTextureTGA((char*)"Tank.tga");
	Texture2D* gunpowderTexture = new Texture2D();
	gunpowderTexture->LoadTextureTGA((char*)"Gunpowder.tga");
	Texture2D* bombTexture = new Texture2D();
	bombTexture->LoadTextureTGA((char*)"BombTexture.tga");
	Texture2D* explosionTexture = new Texture2D();
	explosionTexture->LoadTextureTGA((char*)"Explosion.tga");
	Texture2D* skyboxTexture = new Texture2D();
	skyboxTexture->LoadTextureTGA((char*)"MetalPlate.tga");
	Texture2D* lavaTexture = new Texture2D();
	lavaTexture->LoadTextureTGA((char*)"Lava.tga");

	// Add textures to mesh manager
	_meshManager->AddTexture(texture, "Temp");
	_meshManager->AddTexture(playerDiamondTex, "PlayerDiamond");
	_meshManager->AddTexture(playerDiamondTex2, "PlayerDiamond2");
	_meshManager->AddTexture(diamondBarsTex, "DiamondBars");
	_meshManager->AddTexture(grassTexture, "Grass");
	_meshManager->AddTexture(tankTexture, "Tank");
	_meshManager->AddTexture(gunpowderTexture, "Gunpowder");
	_meshManager->AddTexture(bombTexture, "Bomb");
	_meshManager->AddTexture(explosionTexture, "Explosion");
	_meshManager->AddTexture(skyboxTexture, "Skybox");
	_meshManager->AddTexture(lavaTexture, "Lava");

	// Create Static objects
	_plane = new SceneObject(_meshManager->GetMesh("Platform"), _meshManager->GetTexture("Skybox"), Vector3{ 0, -1, 0 }, Rotation{ 0, 0, 0 }, Vector3{ 1,1,1 });
	_lava = new SceneObject(_meshManager->GetMesh("Lava"), _meshManager->GetTexture("Lava"), Vector3{ 0, -50, 0 }, Rotation{ 0, 0, 0 }, Vector3{ 1,1,1 });
	_skybox = new Skybox(_meshManager->GetMesh("Skybox"), _meshManager->GetTexture("Skybox"), 0, 0, 0);

	// Create Important objects
	_creatures[0] = new Creature(5, 1, 25, 0);
	_creatures[1] = new Creature(0, 1, -25, 1);
	_playerDiamond = new PlayerDiamond(1, 2.5, 25, 0);
	_playerDiamond2 = new PlayerDiamond2(5, 1, -25, 1);

	// Set the diamond targets
	_creatures[0]->SetTargetPointer(_playerDiamond->GetPosPointer()); // Gets the position pointer from diamond and sets it to the creatures target
	_creatures[1]->SetTargetPointer(_playerDiamond2->GetPosPointer());


	// Spawn the gunpowder
	_gunpowder = new PickupObject(_meshManager->GetMesh("Gunpowder"), _meshManager->GetTexture("Gunpowder"), 0, 1, 0);
	_gunpowder->RandomPosition();

	// HUD Objects
	_HudImage = new HUDImage("HUDOutline.tga", 0, 0, 0);
	_heartDisplay = new HUDImage("Heart.tga", 0.3, -0.05, 0);
	_coinDisplay = new HUDImage("CoinHUD.tga", 0.1, -0.05, 0);
	_IngameHUD = new HUDImage("IngameHUD.tga", 0, 0, 0);
	_winnerDisplay = nullptr;


	_menu = true;
	_colorWhite = { 1.0, 1.0, 1.0 };
	_chargePos[0] = { -0.63, -0.79, 0 };
	_chargePos[1] = { 0.63, -0.79, 0 };
		
	// Camera
	camera = new Camera();
	camera->SetTarget(_creatures[0]->GetPosPointer(), _creatures[1]->GetPosPointer());
	camera->SetMode(MENU);

	// Set Score
	_p1Score = 0;

	// Set the initial Bomb
	Vector3 pos = { 0, 100, 0 };
	CreateBomb(&pos);

	// Set up bomb spawning variables
	_bombSpawnRate = 3;
	_bombCurrentRate = _bombSpawnRate;

	// End Game variables
	_endScreen = false;
	_winningCreature = nullptr;
	_endGameWait = 3;
}

void HelloGL::ResetToMenu()
{
	// Reset Players
	_creatures[0]->Reset();
	_creatures[1]->Reset();
	_creatures[0]->SetPos(0, 1, 25);
	_creatures[1]->SetPos(0, 1, -25);

	// Reset Diamonds
	_playerDiamond->SetPos(0, 1, 25);
	_playerDiamond2->SetPos(5, 1, -25);

	// Reset Camera
	camera->SetMode(MENU);
	camera->SetPos(-57.0, 72, 36);
	
	// Clear Bombs
	_bombs.clear();

	// Reset Scores
	_p1Score = 0;

	_endScreen = false;
	_endGameWait = 3;
	_winningCreature = nullptr;

	delete _winnerDisplay;
	_winnerDisplay = nullptr;
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 2.0;
	_lightPosition->z = 0.0;
	_lightPosition->w = 1.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.7;
	_lightData->Ambient.y = 0.7;
	_lightData->Ambient.z = 0.7;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.6;
	_lightData->Diffuse.y = 0.6;
	_lightData->Diffuse.z = 0.6;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 1.0;
	_lightData->Specular.y = 1.0;
	_lightData->Specular.z = 1.0;
	_lightData->Specular.w = 1.0;

}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutPassiveMotionFunc(GLUTCallbacks::mouse_callback);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewport to entire window
	glViewport(0, 0, 800, 800);

	// Set correct perspective
	gluPerspective(45, 1, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
}

void HelloGL::Set2D()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void HelloGL::Set3D()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the scene

	Set3D(); // 3D mode
	glLoadIdentity();

	camera->Look(); // Set Look

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glEnable(GL_LIGHT0);

	_skybox->Draw();
	_lava->Draw();

	if (!_menu) // Draw only when menu isn't up
	{
		_playerDiamond->Draw();
		_playerDiamond2->Draw();
	}


	_plane->Draw();
	_creatures[0]->Draw();
	_creatures[1]->Draw();
	

	for (int i = 0; i < _coins.size(); i++)
	{
		_coins[i]->Draw();
	}

	_gunpowder->Draw();

	for (int i = 0; i < _bombs.size(); i++)
	{
		_bombs[i]->Draw();
	}


	Set2D(); // 2D mode
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);

	if (_menu) // Draw when menu is up
	{	
		_HudImage->Draw();
	}
	else // Draw only ingame
	{
		_IngameHUD->Draw();
		// Ingame Hud Display

		DisplayHealth(); // Draw the Health Bars

		_creatures[0]->DrawChargeBar();
		_creatures[1]->DrawChargeBar();


		DisplayString(std::to_string((int)(_creatures[0]->GetCharge() * 100)).c_str(), &_chargePos[0], &_colorWhite);
		DisplayString(std::to_string((int)(_creatures[1]->GetCharge() * 100)).c_str(), &_chargePos[1], &_colorWhite);

		if (_endScreen)
			_winnerDisplay->Draw();
	}

	glFlush(); // Flush to the graphics card
	glutSwapBuffers();
}

void HelloGL::DisplayHealth()
{
	glPushMatrix();
	for (int i = 0; i < _creatures[0]->GetHealth(); i++) // Loop for however many health
	{
		glTranslatef(0.05, 0, 0);
		_heartDisplay->Draw(); // Draw the heart
	}
	glPopMatrix();

	// Repeat for player 2
	glPushMatrix();
	glTranslatef(1.1, 0, 0);
	for (int i = 0; i < _creatures[1]->GetHealth(); i++)
	{
		glTranslatef(0.05, 0, 0);
		_heartDisplay->Draw();
	}
	glPopMatrix();
}

void HelloGL::DisplayString(const char* text, Vector3* position, Color* color)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(position->x, position->y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::Update()
{
	int t;
	t = glutGet(GLUT_ELAPSED_TIME);
	float _deltaTime = (t - _oldT);
	_deltaTime = _deltaTime / 1000.0f;
	_oldT = t;

	glLoadIdentity();

	if (!_menu) // If the game is being played
	{
		if (!_endScreen) // If the game is currently in play
		{
			// Spawn air bombs to drop
			_bombCurrentRate -= _deltaTime;
			if (_bombCurrentRate <= 0)
			{
				_bombCurrentRate = _bombSpawnRate;
				Vector3 pos = { rand() % 50 - 25, 100, rand() % 50 - 25 };
				CreateBomb(&pos);
			}
		}
		else
		{
			// If not, Trigger the end game wait timer
			_endGameWait -= _deltaTime;
			if (_endGameWait <= 0)
			{
				_menu = true;
				ResetToMenu(); // Then Reset to menu
			}
		}

		// These will update no matter what is going on
		// This creates the "Moveable end screen" look
		_playerDiamond->Update(_deltaTime);
		_playerDiamond2->Update(_deltaTime);
		_creatures[0]->Update(_deltaTime);
		_creatures[1]->Update(_deltaTime);

		// Loop for both of the players
		for (int i = 0; i < 2; i++)
		{
			if (_creatures[i]->CheckForBomb()) // Check if the character is wanting to make a bomb
			{
				CreateBomb(_creatures[i]->GetPosPointer()); // Spawn a bomb at character position
			}
			if (_creatures[i]->GetHealth() == 0 && !_endScreen) // If a players health is 0 and the end screen hasn't been triggered yet
			{
				_endScreen = true; // Trigger the end screen
				if (i) // Find out which creature won and load the winning image
				{
					_winningCreature = _creatures[0];
					_winnerDisplay = new HUDImage("P1Wins.tga", 0, 0, 0);
				}
				else
				{
					_winningCreature = _creatures[1];
					_winnerDisplay = new HUDImage("P2Wins.tga", 0, 0, 0);
				}
				// Change Camera target
				camera->SetTarget(_winningCreature->GetPosPointer());
				camera->SetMode(TARGET);
			}
		}

		// Finish updating Bombs and Pickups
		UpdateBombs(_deltaTime);
		UpdatePickups(_deltaTime);
	}
	else
	{
		// If in menu, Do camera Square movement
		camera->Update(_deltaTime);
	}

	glutPostRedisplay(); // Update frame
}

void HelloGL::UpdatePickups(float deltaTime)
{
	for (int i = 0; i < 2; i++) // For each of the players, run the pickup collision checks
	{
		for (int j = 0; j < _coins.size(); j++)
		{
			_coins[j]->Update(deltaTime);
			if (Collisions::Instance()->Sphere(_creatures[i]->GetSphereCollision(), _coins[j]->GetSphereCollision()))
			{
				_coins[j]->RandomPosition();
				_p1Score += 1;
			}
		}

		_gunpowder->Update(deltaTime);
		if (Collisions::Instance()->Sphere(_creatures[i]->GetSphereCollision(), _gunpowder->GetSphereCollision()))
		{
			_gunpowder->RandomPosition();
			_creatures[i]->IncreaseCharge(0.2);
		}
	}
}

void HelloGL::UpdateBombs(float deltaTime)
{
	int bombDelete = -1;
	for (int i = 0; i < _bombs.size(); i++) // For each active bomb
	{
		if (_bombs[i]->GetDestroyed()) // Check if it is dead
		{
			bombDelete = i;
			continue;
		}

		_bombs[i]->Update(deltaTime); // Update the bomb
		if (_bombs[i]->GetExploding()) // If it is exploding, get the collisions
		{
			for (int j = 0; j < 2; j++)
			{
				if (Collisions::Instance()->Sphere(_creatures[j]->GetSphereCollision(), _bombs[i]->GetSphereCollision()) && !_bombs[i]->GetHitPlayer())
				{
					_creatures[j]->TakeKnockback(*_bombs[i]->GetPosPointer());
					_bombs[i]->HitPlayer();
				}
			}
		}
	}

	if (bombDelete != -1) // Delete 1 bomb per frame
	{
		delete _bombs[bombDelete];
		_bombs.erase(_bombs.begin() + bombDelete);
	}
}

void HelloGL::CreateBomb(Vector3* position)
{
	Bomb* bomb = new Bomb(_meshManager->GetMesh("Bomb"), _meshManager->GetTexture("Bomb"), position->x, position->y, position->z);
	_bombs.push_back(bomb);
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // ESC
		glutLeaveMainLoop();
	if (key == 32) // Space Bar
	{
		if (_menu)
		{
			_menu = false;
			camera->SetTarget(_creatures[0]->GetPosPointer(), _creatures[1]->GetPosPointer());
			camera->SetMode(MULTITARGET);
		}
	}
	_creatures[0]->PlayerInput(key, x, y);
	_creatures[1]->PlayerInput(key, x, y);
	_playerDiamond->PlayerInput(key, x, y);
	_playerDiamond2->PlayerInput(key, x, y);
}


void HelloGL::KeyboardUp(unsigned char key, int x, int y)
{
	_creatures[0]->PlayerInputRelease(key, x, y);
	_creatures[1]->PlayerInputRelease(key, x, y);
	_playerDiamond->PlayerInputRelease(key, x, y);
	_playerDiamond2->PlayerInputRelease(key, x, y);
}

void HelloGL::mouse_callback(int x, int y)
{
	camera->CameraUpdate(x, y);
}

HelloGL::~HelloGL(void)
{

	delete _plane;
	_plane = nullptr;

	delete _playerDiamond;
	_playerDiamond = nullptr;

	_coins.clear();

	delete _gunpowder;
	_gunpowder = nullptr;

	delete camera;
	camera = nullptr;

	_bombs.clear();

	_meshManager->Cleanup();

	delete _creatures[0];
	_creatures[0] = nullptr;
	delete _creatures[1];
	_creatures[1] = nullptr;

	delete _lightPosition;
	_lightPosition = nullptr;

	delete _lightData;
	_lightData = nullptr;

	// CLEAN UP HUD OBJECTS
	delete _HudImage;
	_HudImage = nullptr;

	// HUDIMAGES FOR INGAME
	delete _coinDisplay;
	_coinDisplay = nullptr;
	delete _IngameHUD;
	_IngameHUD = nullptr;
	delete _heartDisplay;
	_heartDisplay = nullptr;
	delete _winnerDisplay;
	_winnerDisplay = nullptr;
}

