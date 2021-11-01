#include "Bomb.h"
#include <iostream>
#include "MeshManager.h"
// Github Edit
Bomb::Bomb(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture,Vector3{ x, y, z }, Rotation{ 0, 0, 0 }, Vector3{ 1, 1, 1 })
{
	// Explosion Radius Setup
	_collisionRadius = 1;

	_explosionRadius = 15;
	_currentRadius = 0;
	_explosionSpeed = 15;
	_fuseTime = 0;
	_bombTriggered = false;
	_hitPlayer = false;
	_destroy = false;

	// AirBombs
	if (_position.y != 1) _airBomb = true;
	else _airBomb = false;

	

	MaterialSetup();
}

Bomb::~Bomb()
{
	delete _material;
	_material = nullptr;
}

void Bomb::Update(float deltaTime)
{
	// If the fuse time has passed, trigger bomb and expand collision radius
	if (!_airBomb)
	{
		if (_fuseTime >= 3)
		{
			SwapMesh(); // Check is bomb has JUST started to explode

			if (_currentRadius < _explosionRadius)
			{
				_currentRadius += deltaTime * _explosionSpeed;
			}
			else
			{
				_destroy = true;
			}
		}
		else
		{
			_fuseTime += deltaTime;
		}
	}
	else
	{
		if (_position.y > 1)
		{
			_position.y -= 50 * deltaTime;
		}
		else
		{
			SwapMesh(); // Check is bomb has JUST started to explode

			if (_currentRadius < _explosionRadius)
			{
				_currentRadius += deltaTime * _explosionSpeed;
			}
			else
			{
				_destroy = true;
			}
		}
	}
}

void Bomb::SwapMesh()
{
	if (!_bombTriggered)
	{
		_mesh = MeshManager::getInstance()->GetMesh("Explosion");
		_texture = MeshManager::getInstance()->GetTexture("Explosion");

		_bombTriggered = true;
	}
}

void Bomb::Draw()
{
	if (_mesh->Normals != nullptr && _mesh->Vertices != nullptr)
	{
		glPushMatrix();

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

		glTranslatef(_position.x, _position.y, _position.z);

		glPushMatrix();
		if (_bombTriggered)
			glScalef(_currentRadius, _currentRadius, _currentRadius); // scale if exploding
		glRotatef(_rotation.Yaw, 0.0f, 1.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, _mesh->IndexCount);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glPopMatrix();
	}
}
void Bomb::MaterialSetup()
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