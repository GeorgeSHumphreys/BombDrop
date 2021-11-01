#include "PlayerDiamond.h"
#include "MeshManager.h"
#include <math.h>
#include <iostream>

PlayerDiamond::PlayerDiamond(float x, float y, float z, int mode) : SceneObject(nullptr, nullptr, Vector3{ x, y, z }, Rotation{ 0, 0, 0 }, Vector3{ 1, 1, 1 })
{
	_movespeed = 15;
	_baseMoveSpeed = _movespeed;
	_fastMoveSpeed = 30;
	_hoverHeight = 0;
	_hoverTime = 0;
	_hoverSpeed = 2;

	// Movement
	_moveVert = 0;
	_moveHoriz = 0;

	_barsObject = new PlayerDiamondBars(0, 0, 0);
	_mesh = MeshManager::getInstance()->GetMesh("PlayerDiamond");
	if (mode == 0)
		_texture = MeshManager::getInstance()->GetTexture("PlayerDiamond");
	else
		_texture = MeshManager::getInstance()->GetTexture("PlayerDiamond2");
	MaterialSetup();
}

PlayerDiamond::~PlayerDiamond()
{
	delete _material;
	_material = nullptr;

	delete _barsObject;
	_barsObject = nullptr;
}

void PlayerDiamond::Draw()
{
	//if (_mesh->VIndices != nullptr && _mesh->Normals != nullptr && _mesh->Vertices != nullptr)
	{
		if (_mesh->Normals != nullptr && _mesh->Vertices != nullptr)
		{
			glPushMatrix();
			glTranslatef(_position.x, _position.y + _hoverHeight, _position.z);
			_barsObject->Draw();

			glBindTexture(GL_TEXTURE_2D, _texture->GetID());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
			glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
			glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
			
			glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
			glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
			glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

			glPushMatrix();
			glScalef(0.6, 0.8, 0.6);
			glRotatef(_rotation.Yaw, 0.0f, 1.0f, 0.0f);
			glDrawArrays(GL_TRIANGLES, 0, _mesh->IndexCount);
			glPopMatrix();

			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glPopMatrix();
		}
	}
}

void PlayerDiamond::Update(float deltaTime)
{
	// Bob up and down
	_hoverHeight = sin(_hoverSpeed * _hoverTime) * 0.8;
	_hoverTime += deltaTime;

	// Move the diamond by player input
	if (_moveVert != 0)
	{
		_position.x += _moveVert * _movespeed * deltaTime;
	}
	if (_moveHoriz != 0)
	{
		_position.z += _moveHoriz * _movespeed * deltaTime;
	}

	_barsObject->Update(deltaTime); // Update child
}

void PlayerDiamond::PlayerInput(unsigned char key, int x, int y)
{
	if (key == 'i')
		_moveVert = 1;
	if (key == 'j')
		_moveHoriz = -1;
	if (key == 'k')
		_moveVert = -1;
	if (key == 'l')
		_moveHoriz = 1;
	if (key == 'n')
		_movespeed = _fastMoveSpeed;

}

void PlayerDiamond::PlayerInputRelease(unsigned char key, int x, int y)
{
	if (key == 'i')
		_moveVert = 0;
	if (key == 'j')
		_moveHoriz = 0;
	if (key == 'k')
		_moveVert = 0;
	if (key == 'l')
		_moveHoriz = 0;
	if (key == 'n')
		_movespeed = _baseMoveSpeed;
}

void PlayerDiamond::SetPos(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void PlayerDiamond::MaterialSetup()
{
	_material = new Material();
	_material->Ambient.x = 1.0; _material->Ambient.y = 1.0; _material->Ambient.z = 1.0;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 1.0; _material->Diffuse.y = 1.0; _material->Diffuse.z = 1.0;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}
