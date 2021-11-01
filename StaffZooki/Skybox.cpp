#include "Skybox.h"
#include <iostream>
//std::string meshName, std::string textureName, Vector3 position, Rotation rotation, Vector3 scale
Skybox::Skybox(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture, Vector3{ x, y, z }, Rotation{ 0, 0, 0 }, Vector3{ 1, 1, 1 })
{
	MaterialSetup();
}

Skybox::~Skybox()
{
	
}


void Skybox::Update()
{

}

void Skybox::MaterialSetup()
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