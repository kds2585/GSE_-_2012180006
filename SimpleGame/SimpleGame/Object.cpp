#include "stdafx.h"
#include "Object.h"



Object::Object()
{
	
}
Object::~Object(){
}
Object::Object(const float sx, const float sy, const int typ, const int sid, const int steam)
	: x(sx), y(sy), colorA(1),
	dx(rand() % WinWid - MidX),
	dy(rand() % WinHei - MidY),
	Life(100), LifeTime(10),
	type(typ), id(sid), team(steam), animation(0)
{
	switch (typ) {
	case CHARA:
		Life = 100;
		spd = 300;
		size = 30;
		CoolDown = CHARACOOL;
		break;
	case BUILDING:
		Life = 500;
		spd = 0;
		size = 100;
		CoolDown = BUILDINGCOOL;
		break;
	case BULLET:
		Life = 15;
		spd = 600;
		size = 4;
		break;
	case ARROW:
		Life = 10;
		spd = 100;
		size = 4;
		break;
	}
	LifeMax = Life;
	if (steam == TeamA) {
		switch (typ) {
		case CHARA:
			colorR = 0;
			colorG = 0;
			colorB = 1;
			break;
		case BUILDING:
			colorR = 1;
			colorG = 1;
			colorB = 1;
			break;
		case BULLET:
			colorR = 0;
			colorG = 0;
			colorB = 1;
			break;
		case ARROW:
			colorR = 1;
			colorG = 1;
			colorB = 0;
			break;
		}
	}
	else if (steam == TeamB) {
		switch (typ) {
		case CHARA:
			colorR = 1;
			colorG = 0;
			colorB = 0;
			break;
		case BUILDING:
			colorR = 1;
			colorG = 1;
			colorB = 1;
			break;
		case BULLET:
			colorR = 1;
			colorG = 0;
			colorB = 0;
			break;
		case ARROW:
			colorR = 0.5;
			colorG = 0.2;
			colorB = 0.7;
			break;
		}
	}

	colorA = 1;
	dx = cos(atan2f(dy - y, dx - x));
	dy = sin(atan2f(dy - y, dx - x));
}




float Object::getX() const  {
	return x;
}
void Object::setX(const float sx) {
	x = sx;
}

float Object::getY() const {
	return y;
}
void Object::setY(const float sy) {
	y = sy;
}

float Object::getSize() const {
	return size;
}
void Object::setSize(const float sSize) {
	size = sSize;
}

float Object::getSpd() const {
	return spd;
}
void Object::setSpd(const float sSpd) {
	spd = sSpd;
}

int Object::getTeam() const {
	return team;
}
void Object::setTeam(const float sSpd) {
	spd = sSpd;
}

float Object::getCool() const {
	return CoolDown;
}
void Object::setCool(const float sCool) {
	CoolDown = sCool;
}

float Object::getDirX() const {
	return dx;
}
void Object::setDirX(const float sdx) {
	dx = sdx;
}
float Object::getDirY() const {
	return dy;
}
void Object::setDirY(const float sdy) {
	dy = -sdy;
}

float Object::getLife() const {
	return Life;
}
void Object::setLife(const float sLif) {
	Life = sLif;
}
float Object::getLifeTime() const {
	return LifeTime;
}
void Object::setLifeTime(const float sLifT) {
	LifeTime = sLifT;
}

int Object::getid() const {
	return id;
}
int Object::getType() const {
	return type;
}

void Object::setColor(const float sc) {
	colorR = sc;
}

void Object::drawObject(Renderer& Rend, const int imgID){
	switch (type) {
	case CHARA:
		if (team == TeamB) {
			Rend.DrawTexturedRectSeq(x, y, 0, size, colorR, colorG, colorB, colorA, imgID, animation, 0, 15, 1, LEVEL_GROUND);
			Rend.DrawSolidRectGauge(x, y + size / 1.5, 0, size, 5, 1, 0, 0, 1, Life / LifeMax, LEVEL_GOD);
		}
		else {
			Rend.DrawTexturedRectSeq(x, y, 0, size, colorR, colorG, colorB, colorA, imgID, animation, 0, 15, 1, LEVEL_GROUND);
			Rend.DrawSolidRectGauge(x, y + size / 1.5, 0, size, 5, 0, 0, 1, 1, Life / LifeMax, LEVEL_GOD);
		}
		break;
	case BUILDING:
		Rend.DrawTexturedRect(x,y,0,size, colorR, colorG, colorB, colorA, imgID, LEVEL_SKY);
		if (team == TeamB)
			Rend.DrawSolidRectGauge(x, y + size / 1.5, 0, size, 5, 1, 0, 0, 1, Life / LifeMax, LEVEL_GOD);
		else
			Rend.DrawSolidRectGauge(x, y + size / 1.5, 0, size, 5, 0, 0, 1, 1, Life / LifeMax, LEVEL_GOD);
		break;
	case BULLET:
		Rend.DrawParticle(x, y, 0, size, colorR, colorG, colorB, colorA, -dx, -dy, imgID, animation);
		//Rend.DrawSolidRect(x, y, 0, size, colorR, colorG, colorB, colorA, LEVEL_UNDERGROUND);
		break;
	case ARROW:
		Rend.DrawSolidRect(x, y, 0, size, colorR, colorG, colorB, colorA, LEVEL_UNDERGROUND);

		break;
	}
}

void Object::update(const float time)
{
	x += spd * dx * time;
	y += spd * dy * time;
	switch (type) {
	case CHARA:
		animation += time * 10;
		if (animation >= 15) {
			animation = 0;
		}
		break;
	case BULLET:
		animation += time;
		break;
	}


	//LifeTime -= time;
	if (x < -MidX) {
		dx = dx * -1;
		x = -MidX;
	}
	else if (x > MidX) {
		dx = dx * -1;
		x = MidX;
	}
	if (y < -MidY) {
		dy = dy * -1;
		y = -MidY;
	}
	else if (y > MidY) {
		dy = dy * -1;
		y = MidY;
	}
}