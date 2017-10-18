#pragma once

#include "Object.h"
#include <list>
#include <random>
#include <time.h>
#include "Renderer.h"

using namespace std;

class SceneMgr {
	list<Object> objList;
	int objNumLimit;
	int NumOfObj;

public:
	SceneMgr();
	~SceneMgr();

	void createObj(const int x, const int y);

	void drawScene(Renderer& Rdr);
	void update();
	bool collision(float cx, float cy);
	bool collision();





};