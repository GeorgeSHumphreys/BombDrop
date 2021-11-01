#include "MathFuncs.h"

namespace MathFuncs
{
	Vector3 Normalise(float x, float y, float z)
	{
		Vector3 output;
		float length = sqrt(x * x + y * y + z * z);
		output.x = x / length;
		output.y = y / length;
		output.z = z / length;

		return output;
	}
}