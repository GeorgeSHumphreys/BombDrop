#include "PlayerDiamondBars.h"
#include <iostream>
#include "MeshManager.h"

PlayerDiamondBars::PlayerDiamondBars(float x, float y, float z) : SceneObject(nullptr, nullptr, Vector3{ x, y, z }, Rotation{ 0, 0, 0 }, Vector3{ 1, 1, 1 })
{
	MaterialSetup();	
	_mesh = MeshManager::getInstance()->GetMesh("DiamondBars");
	_texture = MeshManager::getInstance()->GetTexture("DiamondBars");
}

PlayerDiamondBars::~PlayerDiamondBars()
{

}

void PlayerDiamondBars::Update(float deltaTime)
{
	// Rotate over time
	_rotation.Yaw += deltaTime * 90;
	if (_rotation.Yaw > 180) _rotation.Yaw = -180;
}

void PlayerDiamondBars::MaterialSetup()
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