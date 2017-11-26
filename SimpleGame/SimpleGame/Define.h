#pragma once
#define WinWid 500
#define WinHei 700
enum OBJ { CHARA = 1, BUILDING, BULLET, ARROW };
enum TEAM { TeamA, TeamB };

#define CHARACOOL 1.0
#define BUILDINGCOOL 1.0

#define LEVEL_GOD 0
#define LEVEL_SKY 0.1
#define LEVEL_GROUND 0.2
#define LEVEL_UNDERGROUND 0.3

const int MidX(WinWid / 2);
const int MidY(WinHei / 2);