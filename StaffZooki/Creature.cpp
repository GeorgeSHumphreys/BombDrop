#include "Creature.h"
#include "MathFuncs.h"
#include <iostream>
#include "MeshManager.h"

Creature::Creature(float x, float y, float z, int mode) : SceneObject(nullptr, nullptr, Vector3{ x, y, z }, Rotation{ 0, 0, 0 }, Vector3{ 1, 1, 1 })
{
	// Movement Setup
	_vely = 0;
	_gravity = -9.81;
	_terminal = -1000;
	_movespeed = 9;
	_baseMoveSpeed = _movespeed;
	_fastMoveSpeed = _movespeed * 2;
	_turnSpeed = 360; // Degrees turned per second, 360 = 1 second for full rotate, 720 = 0.5 seconds for full rotate

	// Collision
	_collisionRadius = 1.5;
	_drawCollision = false;

	// Floating diamond
	_localDiamond = new PlayerDiamond(0, 5, 0, mode);

	// Health
	_health = 3;

	// Bomb Bar
	if (mode == 0)
		_bombCharge = new ChargeBar(-1, -0.8, 0);
	else
		_bombCharge = new ChargeBar(0.2, -0.8, 0);
	_trySpawn = false;

	// Bomb collision setup
	_takingKnockback = 0;
	_knockbackForce = 12;
	_knockbackDirection = { 0,0,0 };
	_knockbackTime = 0.5;

	MaterialSetup();

	_mesh = MeshManager::getInstance()->GetMesh("Creature");
	_texture = MeshManager::getInstance()->GetTexture("Tank");

	_mode = mode;
}

Creature::~Creature()
{
	delete _localDiamond;
	_localDiamond = nullptr;

	delete _bombCharge;
	_bombCharge = nullptr;

	delete _material;
	_material = nullptr;
}

void Creature::Draw()
{
	if (_mesh->Normals != nullptr && _mesh->Vertices != nullptr)
	{
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);

		glPushMatrix(); // Push a new matrix after original translate has been applied
		glScalef(0.5, 0.5, 0.5); // Shrink diamond so its not as big as the actual target
		_localDiamond->Draw(); // Draw Diamond
		glPopMatrix(); // Pop the Matrix so the scale is reset


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
		glRotatef(_rotation.Yaw, 0.0f, 1.0f , 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, _mesh->IndexCount);
		glPopMatrix();

		if (_drawCollision)
		{
			glutWireSphere(_collisionRadius, 20, 20);
		}

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glPopMatrix();
	}
}

void Creature::Update(float deltaTime)
{	
	_bombSpawn = false;
	// Check if taking bomb knockback
	if (_knockbackTime <= 0) _takingKnockback = false;
	if (_takingKnockback)
	{
		_knockbackTime -= deltaTime;
		_position.x += _knockbackDirection.x * exp((_knockbackTime) * 5) * _knockbackForce * deltaTime;
		_position.z += _knockbackDirection.z * exp((_knockbackTime) * 5) * _knockbackForce * deltaTime;

		_target->x = _position.x;
		_target->z = _position.z;
	}
	else
	{
		// Else, track normally
		GetDirection();
		MoveFacingDirection(deltaTime);
	}

	// Create Bounds for rotation
	if (_rotation.Yaw > 180) _rotation.Yaw = -179;
	if (_rotation.Yaw < -180) _rotation.Yaw = 179;

	if(_vely >= _terminal) _vely = _vely + (_gravity * deltaTime); // Gravity and Terminal Vel

	_position.y += _vely * deltaTime; // Add Gravity Vel

	// Force object to floor
	if ((_position.y <= 1 && _position.y > 0) && (_position.x > -30 && _position.x < 30 && _position.z < 30 && _position.z > -30))
	{
		_vely = 0;
		_position.y = 1;
	}
	
	if (_position.y < -20 && _health > 0) // If fell off stage
	{
		TakeDamage(1);
		if (_health > 0)
		{
			_position.y = 2;
			_position.x = 0;
			_position.z = 0;
			_target->x = 0;
			_target->z = 0;
		}
	}

	// Bomb Charge Logic
	if (_bombCharge->GetCharge() >= 1 && _trySpawn)
	{
		_bombSpawn = true;
		_bombCharge->SetCharge(0);
	}

	_localDiamond->Update(deltaTime);
	_bombCharge->Update(deltaTime);
	_trySpawn = false;
}

void Creature::MoveFacingDirection(float deltaTime)
{
	if (_target != nullptr)
	{
		// Find the distances between target and object
		float xdist = _target->x - _position.x;
		float zdist = _target->z - _position.z;

		// If within 1 unit, Snap position + reset target
		if (abs(xdist) < 1 && abs(zdist) < 1)
		{

		}
		else
		{
			// MAIN MOVEMENT AND ANGLE FUNC
			float angleDif = _rotation.Yaw - _targetAngle;

			// Find direction needed to rotate and rotate towards it
			if (abs(angleDif) >= 180)
			{
				if (angleDif > 0)
				{
					_rotation.Yaw += _turnSpeed * deltaTime;
				}
				else
				{
					_rotation.Yaw -= _turnSpeed * deltaTime;
				}
			}
			else if (_rotation.Yaw < _targetAngle)
			{
				_rotation.Yaw += _turnSpeed * deltaTime;
			}
			else if (_rotation.Yaw > _targetAngle)
			{
				_rotation.Yaw -= _turnSpeed * deltaTime;
			}

			// If the required angle is within 5 degrees
			if (abs(angleDif) <= _turnSpeed * deltaTime)
			{
				// Snap to correct angle
				_rotation.Yaw = _targetAngle;
			}


			// Same Camera angle application
			// Takes the Yaw and converts it into a Direction Vector
			_direction.x = -sin((_rotation.Yaw * (3.1419 / 180)));
			_direction.y = sin((_rotation.Pitch * (3.1419 / 180)));
			_direction.z = -cos(_rotation.Yaw * (3.1419 / 180)) * cos(_rotation.Pitch * (3.1419 / 180));
			// Apply direction to the position * speed and deltaTime;
			_position.x += _direction.x * _movespeed * deltaTime;
			_position.z += _direction.z * _movespeed * deltaTime;
		}
	}
}

void Creature::SetPos(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Creature::Reset()
{
	_health = 3;
	_bombCharge->SetCharge(0);
}

void Creature::GetDirection()
{
	float xdist = _target->x - _position.x;
	float zdist = _target->z - _position.z;

	float radians = -(atan2(xdist, -zdist)); // Using atan2, and flipping Axis to match OpenGL implement
	_targetAngle = (radians * (180 / 3.1419)); // Convert to -180 -> 180 degrees
}

void Creature::PlayerInput(unsigned char key, int x, int y)
{
	// Check if player 1 or player 2, then check the key
	if (_mode == 0)
	{
		if (key == 'm')
			SpawnBomb();
		if (key == 'n')
			_movespeed = _fastMoveSpeed;
	}
	else
	{
		if (key == 'x')
			SpawnBomb();
		if (key == 'z')
			_movespeed = _fastMoveSpeed;
	}
}

void Creature::PlayerInputRelease(unsigned char key, int x, int y)
{
	if (_mode == 0)
	{
		if (key == 'n')
			_movespeed = _baseMoveSpeed;
	}
	else
	{
		if (key == 'z')
			_movespeed = _baseMoveSpeed;
	}
	

}


void Creature::TakeKnockback(Vector3 bombPos)
{
	// Calculate the ToBomb direction, but don't invert it, so it moves the player backwards
	float xDist, yDist, zDist;
	xDist = _position.x - bombPos.x;
	yDist = _position.y - bombPos.y;
	zDist = _position.z - bombPos.z;

	// Set the bomb variables
	_knockbackDirection = MathFuncs::Normalise(xDist, yDist, zDist);
	_knockbackTime = 0.5;
	_takingKnockback = true;
}

void Creature::MaterialSetup()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.8; _material->Ambient.z = 0.8;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.8; _material->Diffuse.z = 0.8;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

