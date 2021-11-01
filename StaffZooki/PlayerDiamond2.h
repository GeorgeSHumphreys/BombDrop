#pragma once
#include "PlayerDiamond.h"
class PlayerDiamond2 : public PlayerDiamond
{
public:
	PlayerDiamond2(float x, float y, float z, int mode);
	~PlayerDiamond2();

	void PlayerInput(unsigned char key, int x, int y) override;
	void PlayerInputRelease(unsigned char key, int x, int y) override;
private:
};

