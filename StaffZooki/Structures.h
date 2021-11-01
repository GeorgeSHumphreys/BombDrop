#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <iostream>
#include <vector>

class Texture2D;


struct Vector3
{
	float x, y, z;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;

	int VertexCount, NormalCount, TexCoordCount, IndexCount;

};

struct Vector4
{
	float x, y, z, w;
};

struct Lighting
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

struct Material
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	GLfloat Shininess;
};

struct Rotation
{
	float Pitch;
	float Yaw;
	float Roll;
};

struct SphereCollisionInfo
{
	float radius;
	Vector3 position;

	SphereCollisionInfo(float radius, Vector3 position)
	{
		this->radius = radius;
		this->position = position;
	}
};


struct MeshData
{
	Mesh* mesh;
	std::string name;

	MeshData(Mesh* mesh, std::string name)
	{
		this->mesh = mesh;
		this->name = name;
	}
};

struct TextureData
{
	Texture2D* texture;
	std::string name;

	TextureData(Texture2D* texture, std::string name)
	{
		this->texture = texture;
		this->name = name;
	}
};

enum CameraMode
{
	CONTROL,
	TARGET,
	MENU,
	MULTITARGET
};