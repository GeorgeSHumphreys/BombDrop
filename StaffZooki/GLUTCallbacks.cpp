// Includes
#include "GLUTCallbacks.h"
#include "HelloGL.h"

// Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		// Initialise to a null pointer to begin
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		if (helloGL != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			helloGL->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
		}
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		if (helloGL != nullptr)
		{
			helloGL->Keyboard(key, x, y);
		}
	}

	void KeyboardUp(unsigned char key, int x, int y)
	{
		if (helloGL != nullptr)
		{
			helloGL->KeyboardUp(key, x, y);
		}
	}

	void mouse_callback(int x, int y)
	{
		if (helloGL != nullptr)
		{
			helloGL->mouse_callback(x, y);
		}
	}
}