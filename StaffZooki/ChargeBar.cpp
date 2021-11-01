#include "ChargeBar.h"
#include <iostream>

ChargeBar::ChargeBar(float x, float y, float z)
{
	// Position setup
	_position.x = x;
	_position.y = y;
	_position.z = z;

	// Explosion Setup
	_chargePercent = 0;
	_chargeRate = 0.1;
	_barLength = 0.8;
}

ChargeBar::~ChargeBar()
{

}

void ChargeBar::Draw()
{
	// Draw from left position to the right depending on the % charge the bomb has
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(_position.x, _position.y, _position.z);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	glTexCoord2f(0, -1);
	glVertex2f((_chargePercent * _barLength), 0);
	glTexCoord2f(-1, -1);
	glVertex2f((_chargePercent * _barLength), -0.1);
	glTexCoord2f(-1, 0);
	glVertex2f(0, -0.1);
	glEnd();
	glPopMatrix();
}

void ChargeBar::Update(float deltaTime)
{ 
	// Charge to full, unless full
	if (_chargePercent >= 1)
	{
		_chargePercent = 1;
	}
	else
	{
		_chargePercent += deltaTime * _chargeRate;
	}
}
