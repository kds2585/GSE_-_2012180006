/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Define.h"
#include <Windows.h>
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"


using namespace std;



#define MAX_OBJECTS_COUNT 50

SceneMgr m_objects;
bool LButtonDown = false;
DWORD currTime(timeGetTime());
DWORD prevTime(timeGetTime());
float frameTime(0);
float objCreateCDown(0);

void RenderScene(void)
{
	currTime = timeGetTime();
	frameTime = (float)(currTime - prevTime) / 1000.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if (objCreateCDown > 0)
		objCreateCDown -= frameTime;

	m_objects.update(frameTime);
	m_objects.drawScene();

	prevTime = currTime;
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (y > MidY && objCreateCDown <= 0) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			m_objects.createObj(x - MidX, y - MidY, CHARA, TeamA);
			objCreateCDown = 2;
		}
	}


	
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));
	
	m_objects.createObj(0, -MidY / 1.5, BUILDING, TeamB);
	m_objects.createObj(-MidX / 1.5, -MidY / 1.5, BUILDING, TeamB);
	m_objects.createObj(MidX / 1.5, -MidY / 1.5, BUILDING, TeamB);

	m_objects.createObj(0, MidY / 1.5, BUILDING, TeamA);
	m_objects.createObj(-MidX / 1.5, MidY / 1.5, BUILDING, TeamA);
	m_objects.createObj(MidX / 1.5, MidY / 1.5, BUILDING, TeamA);

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinWid, WinHei);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	m_objects.initRenderer(WinWid, WinHei);
	m_objects.imageLoad();



	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

    return 0;
}

