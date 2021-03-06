#include "StaticObject.h"
#include <iostream>
#include <fstream>


StaticObject::StaticObject(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0;
}

StaticObject::~StaticObject()
{
	delete _mesh;
	_mesh = nullptr;
}

void StaticObject::Draw()
{
	if (_mesh->Indices != nullptr && _mesh->Normals != nullptr && _mesh->Vertices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		//glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}


void StaticObject::Update()
{
	//_rotation += 0.1f;
}