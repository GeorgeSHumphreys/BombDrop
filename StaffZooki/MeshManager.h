#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <vector>
#include <iostream>

// Singleton Class to hold mesh and texture data
class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	static MeshManager* getInstance(); // Static means it will be able to be called on whichever class has the include

	Mesh* GetMesh(std::string name);
	Texture2D* GetTexture(std::string name);

	void AddMesh(Mesh* mesh, std::string name);
	void AddTexture(Texture2D* texture, std::string name);

	void ReleaseMesh(std::string name);
	void ReleaseTexture(std::string name);

	void Cleanup();
private:
	static MeshManager* instance; // Static means this is globally set once, if requested it will always bring the same one
	std::vector<MeshData> _meshes;
	std::vector<TextureData> _textures;
};

