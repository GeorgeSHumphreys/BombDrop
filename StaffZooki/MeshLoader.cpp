#include "MeshLoader.h"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

namespace MeshLoader
{
	void LoadObjFiles(ifstream& inFile, Mesh& mesh);
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}


	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;
		mesh.TexCoords = new TexCoord[mesh.TexCoordCount];
		for (int i = 0; i < mesh.TexCoordCount; i++)
		{
			inFile >> mesh.TexCoords[i].u;
			inFile >> mesh.TexCoords[i].v;
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;
		mesh.Indices = new GLushort[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++)
		{
			inFile >> mesh.Indices[i];
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		inFile.close();

		return mesh;
	}


	void LoadObjFiles(ifstream& inFile, Mesh& mesh)
	{
		std::vector <unsigned int> vertexIndices, uIndices, normalIndices;
		std::vector<Vertex> temp_vertices;
		std::vector<TexCoord> temp_uvs;
		std::vector<Vector3> temp_normals;


		string test;
		while (!inFile.eof())
		{
			inFile >> test; // Load next number


			if (test == "v") // If a vertex, store in vertex
			{
				Vertex vertex;
				inFile >> vertex.x;
				inFile >> vertex.y;
				inFile >> vertex.z;
				temp_vertices.push_back(vertex);
			}
			else if (test == "vt") // if a tex coord, store in UVs
			{
				TexCoord texcoord;
				inFile >> texcoord.u;
				inFile >> texcoord.v;
				temp_uvs.push_back(texcoord);
			}
			else if (test == "vn") // if a normal, store in normal
			{
				Vector3 normals;
				inFile >> normals.x;
				inFile >> normals.y;
				inFile >> normals.z;
				temp_normals.push_back(normals);
			}
			else if (test == "f") // If it is an F = indices
			{
				for (int i = 0; i < 3; i++)
				{
					inFile >> test; // Load first set of 3


					std::replace(test.begin(), test.end(), '/', ' '); // Remove "/"

					stringstream ss(test);
					GLushort temp;

					// Pull each number out and store in each Indices
					ss >> temp;
					vertexIndices.push_back(temp-1);
					ss >> temp;
					uIndices.push_back(temp-1);
					ss >> temp;
					normalIndices.push_back(temp-1);
				}
			}
		}
		mesh.IndexCount = vertexIndices.size(); // Set Index count

		// Testing for Draw Elements
		
		mesh.Normals = new Vector3[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++) // Set normals by the order of the NormalIndices, Repeated normals but will be in a raw order for Draw arrays
		{
			mesh.Normals[i] = temp_normals[normalIndices[i]];
		}

		mesh.TexCoords = new TexCoord[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++) // Set TexCoords by the order of the TexCoordsIndices, Repeated normals but will be in a raw order for Draw arrays
		{
			mesh.TexCoords[i] = temp_uvs[uIndices[i]];
		}

		mesh.Vertices = new Vertex[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++) // Set Vertices by the order of the VerticesIndices, Repeated normals but will be in a raw order for Draw arrays
		{
			mesh.Vertices[i] = temp_vertices[vertexIndices[i]];
		}
	}

	Mesh* MeshLoader::LoadObj(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadObjFiles(inFile, *mesh);

		inFile.close();

		return mesh;
	}
}