#include "MeshManager.h"
#include "Texture2D.h"

MeshManager* MeshManager::instance = nullptr;
// Set up as singleton

MeshManager::MeshManager()
{
	instance = this;
}
MeshManager::~MeshManager()
{

}

MeshManager* MeshManager::getInstance()
{
	return instance;
} 

Mesh* MeshManager::GetMesh(std::string name)
{
	// Return a mesh based on name
	Mesh* buffer = new Mesh();
	for (int i = 0; i < _meshes.size(); i++)
	{
		if (_meshes[i].name == name)
		{
			return _meshes[i].mesh;
		}
	}
	std::cerr << "Mesh doesn't exist in vector";
	return buffer;
}

Texture2D* MeshManager::GetTexture(std::string name)
{
	// Return a texture based on name
	Texture2D* buffer = new Texture2D();
	for (int i = 0; i < _textures.size(); i++)
	{
		if (_textures[i].name == name)
		{
			return _textures[i].texture;
		}
	}
	std::cerr << "Mesh doesn't exist in vector";
	return buffer;
}

void MeshManager::AddMesh(Mesh* mesh, std::string name)
{
	// Save mesh in the meshes
	MeshData buffer = { mesh, name };
	_meshes.push_back(buffer);
}

void MeshManager::AddTexture(Texture2D* texture, std::string name)
{
	// Save texture in textures
	TextureData buffer = { texture, name };
	_textures.push_back(buffer);
}

void MeshManager::ReleaseMesh(std::string name)
{
	// Find mesh by name and delete it
	for (int i = 0; i < _meshes.size(); i++)
	{
		if (_meshes[i].name == name)
		{
			delete _meshes[i].mesh;
			_meshes.erase(_meshes.begin() + i);
			break;
		}
	}
}

void MeshManager::ReleaseTexture(std::string name)
{
	// Find texture by name and delete it
	for (int i = 0; i < _textures.size(); i++)
	{
		if (_textures[i].name == name)
		{
			delete _textures[i].texture;
			_textures.erase(_textures.begin() + i);
			break;
		}
	}
}


void MeshManager::Cleanup()
{
	// Loop through everything and delete
	for (int i = 0; i < _textures.size(); i++)
	{
		delete _textures[i].texture;
	}
	for (int i = 0; i < _meshes.size(); i++)
	{
		delete _meshes[i].mesh;
	}

	_textures.clear();
	_meshes.clear();
}