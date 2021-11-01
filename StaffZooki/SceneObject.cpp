#include "SceneObject.h"
#include "Texture2D.h"
#include "MeshManager.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture, Vector3 position, Rotation rotation, Vector3 scale)
{
	_mesh = mesh;
	_texture = texture;

	_position = position;
	_rotation = rotation;
	_scale = scale;
};

SceneObject::~SceneObject() {}

void SceneObject::Update() {}

void SceneObject::Draw()
{
	if (_material == nullptr)
	{
		MaterialSetup();
	}

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
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation.Yaw, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotation.Pitch, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation.Roll, 0.0f, 0.0f, 1.0f);
		glScalef(_scale.x, _scale.y, _scale.z);
		glDrawArrays(GL_TRIANGLES, 0, _mesh->IndexCount);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glPopMatrix();
	}
}

void SceneObject::MaterialSetup()
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