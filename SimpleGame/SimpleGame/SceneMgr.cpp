#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	objNumLimit = 50;
	
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::createObj(const int x, const int y)
{
	if (NumOfObj < objNumLimit) {
		++NumOfObj;
		objList.emplace_back(x - 250, -y + 250, 10, 1, 1, 1, 0, (rand() % 9 + 1) / 10.0, (rand() % 1 - 1), (rand() % 1 - 1));
	}
}

void SceneMgr::drawScene(Renderer& Rdr)
{
	for (auto& d : objList) {
		d.drawObject(Rdr);
	}
}

void SceneMgr::update()
{
	for (auto& d : objList) {
		d.update();
	}
}

bool SceneMgr::collision(float cx, float cy)
{
	for (auto& d : objList) {
		if ((d.getX() <= cx && d.getX() >= cx) && (d.getY() <= cy && d.getY() >= cy)) {
			return true;
		}
		return false;
	}
}
