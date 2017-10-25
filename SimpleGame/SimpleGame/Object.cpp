#include "stdafx.h"
#include "Object.h"


Object::Object()
	: x(0), y(0), size(10), colorR(0), colorG(0), colorB(0), colorA(0), spd(0.1),dx(0),dy(250), Life(100), LifeTime(100)
{
	
}
Object::Object(float sx, float sy, float sSiz, float sRed, float sGreen, float sBlue, float sAlpha, float sSpd)
	: x(sx), y(sy), size(sSiz), colorR(sRed),
	colorG(sGreen), colorB(sBlue), colorA(sAlpha),
	spd(sSpd), dx(0), dy(0), Life(100), LifeTime(100)
{

}
Object::Object(float sx, float sy, float sSiz, float sRed, float sGreen, float sBlue, float sAlpha, float sSpd, float sdx, float sdy)
	: x(sx), y(sy), size(sSiz), colorR(sRed),
	colorG(sGreen), colorB(sBlue), colorA(sAlpha),
	spd(sSpd), dx(sdx), dy(sdy), Life(100), LifeTime(100)
{
	dx = cos(atan2f(dy - y, dx - x));
	dy = sin(atan2f(dy - y, dx - x));
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

float Object::getLife() const {
	return Life;
}
void Object::setLife(const float& sLif) {
	Life = sLif;
}
float Object::getLifeTime() const {
	return LifeTime;
}
void Object::setLifeTime(const float& sLifT) {
	LifeTime = sLifT;
}

void Object::setColor(const float& sc) {
	colorR = sc;
}

void Object::drawObject(Renderer& Rend){
	Rend.DrawSolidRect(x, y, 0, size, colorR, colorG, colorB, colorA);
}

void Object::update(unsigned int time)
{
	//x += cos(atan2f(dy - y, dx - x)) * spd;
	//y += sin(atan2f(dy - y, dx - x)) * spd;
	x += spd * dx * time;
	y += spd * dy * time;
	if (x < -250) {
		dx = dx * -1;
		x = -250;
	}
	else if (x > 250) {
		dx = dx * -1;
		x = 250;
	}
	if (y < -250) {
		dy = dy * -1;
		y = -250;
	}
	else if (y > 250) {
		dy = dy * -1;
		y = 250;
	}
}