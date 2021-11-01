#include "PickupObject.h"

PickupObject::PickupObject(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture, Vector3{ x, y, z }, Rotation{ 0, 0, 0 }, Vector3{ 1, 1, 1 })
{
	_rotationSpeed = 270;

	_collisionRadius = 1;
	_drawCollision = false;

	_hoverHeight = 0;
	_hoverTime = 0;
	_hoverSpeed = 4;

	MaterialSetup();
}

PickupObject::~PickupObject()
{
	delete _mesh;
	_mesh = nullptr;

	delete _material;
	_material = nullptr;
}

void PickupObject::Draw()
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

		glPushMatrix();
		glTranslatef(_position.x, _position.y + _hoverHeight, _position.z);

		if (_drawCollision)
		{
			glutWireSphere(_collisionRadius, 20, 20);
		}

		glRotatef(_rotation.Yaw, 0.0f, 1.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, _mesh->IndexCount);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glPopMatrix();
	}
}

void PickupObject::Update(float deltaTime)
{
	// Rotate and bob up and down
	_rotation.Yaw += _rotationSpeed * deltaTime * 0.5;

	if (_rotation.Yaw > 180) _rotation.Yaw = -180;

	_hoverHeight = sin(_hoverSpeed * _hoverTime) * 0.8;
	_hoverTime += deltaTime;
}

void PickupObject::RandomPosition()
{
	_position.x = (rand() % 60) - 30;
	_position.z = (rand() % 60) - 30;
}

void PickupObject::MaterialSetup()
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