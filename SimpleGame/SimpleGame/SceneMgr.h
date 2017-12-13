#pragma once

#include "Object.h"
#include "Sound.h"
#include <list>
#include <random>
#include <time.h>
#include "Renderer.h"
#include "Define.h"


//enum OBJ { CHARA, BUILDING, BULLET, ARROW }; 디파인 헤더에 있음.

using namespace std;
class SceneMgr {
	list<Object> objList;
	Renderer *m_renderer;
	Sound *m_sound;
	int objNumLimit;
	int NumOfObj;
	int ImageNumber[6];
	int SoundNum[2];
	double m_time;
public:
	SceneMgr();
	~SceneMgr();
	void createObj(const int x, const int y, const int type, const int team);

	void createObjSon(const int x, const int y, const int type, const int pid, const int team);

	void drawScene();
	void update(float time);
	void initRenderer(int xl, int yl);
	void initSound();
	void imageLoad();
	bool collision(int rtx1, int rty1, int rbx1, int rby1, int rtx2, int rty2, int rbx2, int rby2);






};