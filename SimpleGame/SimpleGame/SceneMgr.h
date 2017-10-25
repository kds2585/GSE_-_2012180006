#pragma once

#include <Windows.h>
#include "Object.h"
#include <list>
#include <random>
#include <time.h>
#include "Renderer.h"

using namespace std;
class SceneMgr {
	list<Object> objList;
	Renderer *m_renderer;
	int objNumLimit;
	int NumOfObj;

public:
	SceneMgr();
	~SceneMgr();
	void createObj(const int x, const int y);

	void drawScene(Renderer& Rdr);
	void drawScene();
	void update();
	void initRenderer();
	bool collision(int rtx1, int rty1, int rbx1, int rby1, int rtx2, int rty2, int rbx2, int rby2);






};