#include "stdafx.h"
#include "Object.h"


Object::Object()
	: x(0), y(0), size(10), colorR(0), colorG(0), colorB(0), colorA(0), spd(1),dx(0),dy(250)
{

}

Object::Object(float sx, float sy, float sSiz, float sRed, float sGreen, float sBlue, float sAlpha, float sSpd)
	: x(sx), y(sy), size(sSiz), colorR(sRed), colorG(sGreen), colorB(sBlue), colorA(sAlpha), spd(sSpd), dx(0), dy(0)
{

}

float Object::getX() const  {
	return x;
}
void Object::setX(const float& sx) {
	x = sx;
}

float Object::getY() const {
	return y;
}
void Object::setY(const float& sy) {
	y = sy;
}

float Object::getSize() const {
	return size;
}
void Object::setSize(const float& sSize) {
	size = sSize;
}

float Object::getSpd() const {
	return spd;
}
void Object::setSpd(const float& sSpd) {
	spd = sSpd;
}

float Object::getDirX() const {
	return dx;
}
void Object::setDirX(const float& sdx) {
	dx = sdx;
}
float Object::getDirY() const {
	return dy;
}
void Object::setDirY(const float& sdy) {
	dy = -sdy;
}

void Object::drawObject(Renderer& Rend){
	Rend.DrawSolidRect(x, y, 0, size, colorR, colorG, colorB, colorA);
}

void Object::update() {
	x += cos(atan2f(dy - y, dx - x)) * spd;
	y += sin(atan2f(dy - y, dx - x)) * spd;
	if (x < -250) {
		x = -250;
	}
	else if (x > 250) {
		x = 250;
	}
	if (y < -250) {
		y = -250;
	}
	else if (y > 250) {
		y = 250;
	}
}