#pragma once
#include "Renderer.h"
#include "Define.h"



class Object {
protected:
	float x, y, size;
	float colorR, colorG, colorB, colorA;
	float spd;
	float dx, dy;
	float Life;
	float LifeTime;
	float CoolDown;
	int type;
	int team;
	int id;
public:
	Object();
	~Object();
	Object(const float sx, const float sy, const int typ, const int sid, const int steam);

	float getX() const;

	float getY() const;

	float getSize() const;

	void setX(const float sx);

	void setY(const float sy);

	void setSize(const float sSize);

	float getSpd() const;

	void setSpd(const float sSpd);


	int getTeam() const;

	void setTeam(const float sSpd);

	float getCool() const;

	void setCool(const float sCool);

	float getDirX() const;

	void setDirX(const float sdx);

	float getDirY() const;

	void setDirY(const float sdy);

	float getLife() const;

	void setLife(const float sLif);

	float getLifeTime() const;

	int getid() const;

	void setLifeTime(const float sLifT);

	int getType() const;

	void setColor(const float sc);

	void drawObject(Renderer & Rend, const int imgID);

	void update(const float time);


};