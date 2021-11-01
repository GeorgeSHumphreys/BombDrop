#pragma once

#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	Mesh* LoadObj(char* path);
};

