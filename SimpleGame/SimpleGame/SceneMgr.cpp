#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	objNumLimit = 200;
}

SceneMgr::~SceneMgr()
{
	delete m_renderer;
}

void SceneMgr::createObj(const int x, const int y, const int type, const int team)
{
	static int id(0);
	if (NumOfObj < objNumLimit) {
		objList.emplace_back(x, -y, type, id, team);
		++NumOfObj;
		++id;
	}
}
void SceneMgr::createObjSon(const int x, const int y, const int type, const int pid, const int team)
{
	if (NumOfObj < objNumLimit) {
		if (type == ARROW || type == BULLET) {
			objList.emplace_back(x, -y, type, pid, team);
		}
		++NumOfObj;
	}
}

void SceneMgr::drawScene()
{
	for (auto& d : objList) {
		if(d.getTeam() == TeamA)
			d.drawObject(*m_renderer, BImage[0]);
		else if (d.getTeam() == TeamB) {
			d.drawObject(*m_renderer, BImage[1]);
		}
	}
	
}

void SceneMgr::update(float time)
{
	static float count(0);
	count += time;
	for (auto& d = objList.begin(); d != objList.end(); d++) {
		d->update(time);
		//충돌체크시 판정
		for (auto& c : objList) {
			if (!(d->getX() == c.getX() && d->getY() == c.getY())) {
				if (collision(d->getX() - d->getSize() / 2, d->getY() - d->getSize() / 2, d->getX() + d->getSize() / 2, d->getY() + d->getSize() / 2,
							  c.getX() - c.getSize() / 2, c.getY() - c.getSize() / 2, c.getX() + c.getSize() / 2, c.getY() + c.getSize() / 2)) {
					if (d->getTeam() != c.getTeam()) {
						if (d->getType() == CHARA && c.getType() == BUILDING) {
							c.setLife(c.getLife() - d->getLife());
							d->setLife(0);
						}
						if ((d->getType() == CHARA || d->getType() == BUILDING) &&
							(c.getType() == ARROW || c.getType() == BULLET))
						{
							d->setLife(d->getLife() - c.getLife());
							c.setLife(0);
							//if (d->getid() != c.getid()) {} id 이용가치가 없어짐
						}
					}
				}
			}
		}
		if (d->getLife() <= 0 || d->getLifeTime() <= 0) {		
			d = objList.erase(d);
			NumOfObj--;
			if (d == objList.end()) {
				break;
			}
		}
	}
	if (count >= 1) {
		createObj(rand() % WinWid - MidX, rand() % MidY - MidY, CHARA, TeamB);
		count = 0;
	}
	for (auto& d : objList) {
		if (d.getCool() <= 0) {
			if (d.getType() == BUILDING) {
				createObjSon(d.getX(), -d.getY(), BULLET, d.getid(), d.getTeam());
				d.setCool(CHARACOOL);
			}
			if (d.getType() == CHARA) {
				createObjSon(d.getX(), -d.getY(), ARROW, d.getid(), d.getTeam());
				d.setCool(BUILDINGCOOL);
			}
		}
		else {
			d.setCool(d.getCool() - time);
		}
	}

}

void SceneMgr::initRenderer(int xl, int yl) {
	m_renderer = new Renderer(xl, yl);
}
void SceneMgr::imageLoad() {
	BImage[0] = m_renderer->CreatePngTexture("Resource/aa.png");
	BImage[1] = m_renderer->CreatePngTexture("Resource/bb.png");
}
bool SceneMgr::collision(int rtx1, int rty1, int rbx1, int rby1, int rtx2, int rty2, int rbx2, int rby2)
{
	if ((rtx1 <= rbx2 && rbx1 >= rtx2) && (rty1 <= rby2 && rby1 >= rty2)) {
		return true;
	}
	return false;
}
