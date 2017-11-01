#pragma once
#include "Renderer.h"

enum OBJ { CHARA, BUILDING, BULLET, ARROW };

class Object {
protected:
	float x, y, size;
	float colorR, colorG, colorB, colorA;
	float spd;
	float dx, dy;
	float Life;
	float LifeTime;
	int type;
public:
	Object();
	~Object();
	Object(float sx, float sy, float sSiz, float sRed, float sGreen, float sBlue, float sAlpha, float sSpd, float sdx, float sdy);

	Object(float sx, float sy, int type);

	Object(float sx, float sy, float sSiz, float sRed, float sGreen, float sBlue, float sAlpha, float sSpd);

	float getX() const;

	float getY() const;

	float getSize() const;

	void setX(const float & sx);

	void setY(const float & sy);

	void setSize(const float & sSize);

	float getSpd() const;

	void setSpd(const float& sSpd);

	float getDirX() const;

	void setDirX(const float & sdx);

	float getDirY() const;

	void setDirY(const float & sdy);

	float getLife() const;

	void setLife(const float & sLif);

	float getLifeTime() const;

	void setLifeTime(const float & sLifT);

	int getType();

	void setColor(const float & sc);

	void drawObject(Renderer& Rend);

	void update(float time);


};