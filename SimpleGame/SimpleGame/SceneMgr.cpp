#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	objNumLimit = 50;
}

SceneMgr::~SceneMgr()
{
	delete m_renderer;
}

void SceneMgr::createObj(const int x, const int y)
{
	if (NumOfObj < objNumLimit) {
		++NumOfObj;
		objList.emplace_back(x - 250, -y + 250, 10, 1, 1, 1, 0, (rand() % 2 + 1) / 10.0, (rand() % 1 - 1), (rand() % 1 - 1));
	}
}

void SceneMgr::drawScene(Renderer& Rdr)
{
	for (auto& d : objList) {
		d.drawObject(Rdr);
	}
}

void SceneMgr::drawScene()
{
	for (auto& d : objList) {
		d.drawObject(*m_renderer);
	}
}

void SceneMgr::update()
{
	DWORD currTime = timeGetTime();
	
	auto p = objList.begin();
	for (auto& d : objList) {
		
		d.update(timeGetTime() - currTime);
		d.setColor(1);
		for (auto& c : objList) {
			if (!(d.getX() == c.getX() && d.getY() == c.getY())) {
				if (collision(d.getX() - d.getSize() / 2, d.getY() - d.getSize() / 2, d.getX() + d.getSize() / 2, d.getY() + d.getSize() / 2,
					c.getX() - c.getSize() / 2, c.getY() - c.getSize() / 2, c.getX() + c.getSize() / 2, c.getY() + c.getSize() / 2)) {
					d.setColor(0);
				}
			}
		}
	}

	
}

void SceneMgr::initRenderer() {
	m_renderer = new Renderer(500, 500);
}

bool SceneMgr::collision(int rtx1, int rty1, int rbx1, int rby1, int rtx2, int rty2, int rbx2, int rby2)
{
	if ((rtx1 <= rbx2 && rbx1 >= rtx2) && (rty1 <= rby2 && rby1 >= rty2)) {
		return true;
	}
	return false;
}
