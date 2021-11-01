#include "HUDImage.h"

HUDImage::HUDImage(std::string path, float x, float y, float z, float sx, float sy, float sz)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_scale.x = sx;
	_scale.y = sy;
	_scale.z = sz;
	_rotation.Pitch = 0;
	_rotation.Yaw = 0;
	_rotation.Roll = 0;

	_texture= new Texture2D();
	_texture->LoadTextureTGA((char*)path.c_str());
	float texHeight, texWidth;
	texHeight = _texture->GetHeight();
	texWidth = _texture->GetWidth();

	xBounds = (texWidth / 800) * 2 - 1;
	yBounds = (texHeight / 800) * 2 - 1;
}

HUDImage::~HUDImage()
{

}

void HUDImage::Update(float deltaTime)
{

}

void HUDImage::Draw()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glScalef(_scale.x, _scale.y, _scale.z);
	glTranslatef(_position.x, _position.y, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-1, 1);
	glTexCoord2f(0, 0);
	glVertex2f(xBounds, 1);
	glTexCoord2f(0, -1);
	glVertex2f(xBounds, -yBounds);
	glTexCoord2f(-1, -1);
	glVertex2f(-1, -yBounds);
	glTexCoord2f(-1, 0);
	glEnd();
	glPopMatrix();
}