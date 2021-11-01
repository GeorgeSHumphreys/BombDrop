#include "PlayerDiamond2.h"
#include "MeshManager.h"

PlayerDiamond2::PlayerDiamond2(float x, float y, float z, int mode) : PlayerDiamond(x, y, z, mode)
{
	//_texture = MeshManager::getInstance()->GetTexture("");
}

PlayerDiamond2::~PlayerDiamond2()
{

}

void PlayerDiamond2::PlayerInput(unsigned char key, int x, int y)
{
	if (key == 'w')
		_moveVert = 1;
	if (key == 'a')
		_moveHoriz = -1;
	if (key == 's')
		_moveVert = -1;
	if (key == 'd')
		_moveHoriz = 1;
	if (key == 'z')
		_movespeed = _fastMoveSpeed;
} 
void PlayerDiamond2::PlayerInputRelease(unsigned char key, int x, int y)
{
	if (key == 'w')
		_moveVert = 0;
	if (key == 'a')
		_moveHoriz = 0;
	if (key == 's')
		_moveVert = 0;
	if (key == 'd')
		_moveHoriz = 0;
	if (key == 'z')
		_movespeed = _baseMoveSpeed;
}