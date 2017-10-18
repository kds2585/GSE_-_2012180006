#pragma once
#include "Renderer.h"


class Object {
protected:
	float x, y, size;
	float colorR, colorG, colorB, colorA;
	float spd;
	int dx, dy;
public:
	Object();

	Object(float sx, float sy, float sSiz, float sRed, float sGreen, float sBlue, float sAlpha, float sSpd, float dx, float dy);

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

	void drawObject(Renderer& Rend);

	void update();


};