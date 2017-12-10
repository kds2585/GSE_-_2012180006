#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	objNumLimit = 200;
}

SceneMgr::~SceneMgr()
{
	delete m_renderer;
	delete m_sound;
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
	m_renderer->DrawTexturedRect(0, 0, 0, WinHei, 1, 1, 1, 1, BImage[2], 0.9);
	for (auto& d : objList) {
		if (d.getTeam() == TeamA) {
			switch (d.getType()) {
			case BUILDING:
				d.drawObject(*m_renderer, BImage[0]);
				break;
			case CHARA:
				d.drawObject(*m_renderer, BImage[3]);
				break;
			case BULLET:
				d.drawObject(*m_renderer, BImage[4]);
				break;
			default:
				d.drawObject(*m_renderer, 0);
				break;
			}
		}
		else if (d.getTeam() == TeamB) {
			switch (d.getType()) {
			case BUILDING:
				d.drawObject(*m_renderer, BImage[1]);
				break;
			case CHARA:
				d.drawObject(*m_renderer, BImage[3]);
				break;
			case BULLET:
				d.drawObject(*m_renderer, BImage[4]);
				break;
			default:
				d.drawObject(*m_renderer, 0);
				break;
			}
		}
	}
	
}

void SceneMgr::update(float time)
{
	static float count(0);
	count += time;
	for (auto& d = objList.begin(); d != objList.end();) {
		d->update(time);
		//�浹üũ ����
		for (auto& c : objList) {
			if (d->getTeam() != c.getTeam()) {
				if (collision(d->getX() - d->getSize() / 2, d->getY() - d->getSize() / 2, d->getX() + d->getSize() / 2, d->getY() + d->getSize() / 2,
							  c.getX() - c.getSize() / 2, c.getY() - c.getSize() / 2, c.getX() + c.getSize() / 2, c.getY() + c.getSize() / 2)) {
					if (d->getType() == CHARA && c.getType() == BUILDING) {
						m_sound->PlaySound(SoundNum[1], false, 0.2f);
						c.setLife(c.getLife() - d->getLife());
						d->setLife(0);
					}
					if ((d->getType() == ARROW || d->getType() == BULLET) &&
						(c.getType() == CHARA || c.getType() == BUILDING))
					{
						m_sound->PlaySound(SoundNum[1], false, 0.2f);
						c.setLife(c.getLife() - d->getLife());
						d->setLife(0);
					}
				}
			}
		}
		//�߻�ü�� ȭ������� ������ ó��
		if (d->getType() == ARROW || d->getType() == BULLET) {
			if (!collision(d->getX() + d->getSize() / 2, d->getY() + d->getSize() / 2, d->getX() - d->getSize() / 2, d->getY() - d->getSize() / 2,
				-MidX, -MidY, MidX, MidY)) {
				d->setLife(0);
			}
		}
		//������Ʈ�� ��ٿ� ���� �ൿ
		if (d->getCool() <= 0) {
			if (d->getType() == BUILDING) {
				createObjSon(d->getX(), -d->getY(), BULLET, d->getid(), d->getTeam());
				d->setCool(CHARACOOL);
			}
			if (d->getType() == CHARA) {
				createObjSon(d->getX(), -d->getY(), ARROW, d->getid(), d->getTeam());
				d->setCool(BUILDINGCOOL);
			}
		}
		else {
			d->setCool(d->getCool() - time);
		}
		//������Ʈ�� �������� 0�϶� ����ó��
		if (d->getLife() <= 0 || d->getLifeTime() <= 0) {
			d = objList.erase(d);
			NumOfObj--;
			continue;
		}
		d++;
	}

	//1�ʸ��� �� ����
	if (count >= 1) {
		createObj(rand() % WinWid - MidX, rand() % MidY - MidY, CHARA, TeamB);
		count = 0;
	}
}

void SceneMgr::initRenderer(int xl, int yl) {
	m_renderer = new Renderer(xl, yl);
}

void SceneMgr::initSound() {
	m_sound = new Sound;
	SoundNum[0] = m_sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	SoundNum[1] = m_sound->CreateSound("./Dependencies/SoundSamples/explosion.wav");
	m_sound->PlaySound(SoundNum[0], true, 0.2f);
}

void SceneMgr::imageLoad() {
	BImage[0] = m_renderer->CreatePngTexture("Resource/aa.png");
	BImage[1] = m_renderer->CreatePngTexture("Resource/bb.png");
	BImage[2] = m_renderer->CreatePngTexture("Resource/BG.png");
	BImage[3] = m_renderer->CreatePngTexture("Resource/Char.png");
	BImage[4] = m_renderer->CreatePngTexture("Resource/part.png");

}
bool SceneMgr::collision(int rtx1, int rty1, int rbx1, int rby1, int rtx2, int rty2, int rbx2, int rby2)
{
	if ((rtx1 <= rbx2 && rbx1 >= rtx2) && (rty1 <= rby2 && rby1 >= rty2)) {
		return true;
	}
	return false;
}
