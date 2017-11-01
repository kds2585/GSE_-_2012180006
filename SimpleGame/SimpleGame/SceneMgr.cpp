#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	objNumLimit = 200;
	preTime = timeGetTime();
	currTime = timeGetTime();
}

SceneMgr::~SceneMgr()
{
	delete m_renderer;
}

void SceneMgr::createObj(const int x, const int y, const int type)
{
	if (NumOfObj < objNumLimit) {
		++NumOfObj;
		objList.emplace_back(x, -y, type);
	}
}

void SceneMgr::drawScene()
{
	for (auto& d : objList) {
		d.drawObject(*m_renderer);
	}
	
}

void SceneMgr::update(float time)
{
	static float count(0);
	count += time;


	for (auto& d = objList.begin(); d != objList.end(); d++) {
		d->update(time);
		if (count > 1 && d->getType() == BUILDING) {
			createObj(d->getX(), d->getY(), BULLET);
			count = 0;
		}
		for (auto& c : objList) {
			if (!(d->getX() == c.getX() && d->getY() == c.getY())) {
				if (collision(d->getX() - d->getSize() / 2, d->getY() - d->getSize() / 2, d->getX() + d->getSize() / 2, d->getY() + d->getSize() / 2,
							  c.getX() - c.getSize() / 2, c.getY() - c.getSize() / 2, c.getX() + c.getSize() / 2, c.getY() + c.getSize() / 2)) {
					if (d->getType() == CHARA && c.getType() == BUILDING) {
						c.setLife(c.getLife() - d->getLife());
						d->setLife(0);
					}
					else if (d->getType() == CHARA && c.getType() == BULLET) {
						d->setLife(d->getLife() - c.getLife());
						c.setLife(0);
					}
				}
			}
		}
		if (d->getLife() <= 0) {
			d = objList.erase(d);
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
