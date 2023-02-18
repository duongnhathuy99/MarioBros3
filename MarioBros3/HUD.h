#pragma once
#include "PlayScene.h"

#define ID_WORLD_SCENE 1
#define ID_SPRITE_HUD_BOARD 65000
#define ID_SPRITE_HUD_BACKGROUND 65001

#define ID_SPRITE_NUMBER_0 65010
#define ID_SPRITE_NUMBER_1 65011
#define ID_SPRITE_NUMBER_2 65012
#define ID_SPRITE_NUMBER_3 65013
#define ID_SPRITE_NUMBER_4 65014
#define ID_SPRITE_NUMBER_5 65015
#define ID_SPRITE_NUMBER_6 65016
#define ID_SPRITE_NUMBER_7 65017
#define ID_SPRITE_NUMBER_8 65018
#define ID_SPRITE_NUMBER_9 65019

#define ID_SPRITE_POWER 65020
#define ID_SPRITE_POWER_P 65021

#define ID_SPRITE_END_SCENE 65022
#define ID_SPRITE_MUSHROOM 65023
#define ID_SPRITE_FIRE_FLOWER 65024
#define ID_SPRITE_STAR 65025

#define DISTANCE_HUD_HEIGHT 24
#define TIME_START_PLAYSCENE 300
#define MILI_1000_SECOND 1000
#define POINT_50 50
#define MAP_HORIZONTAL_LIMIT 2800

class HUD
{
	static HUD* __instance;
	int coin = 0;
	int PowerMeter = 0;
	int point = 0;
	int health = 4;
	int time = 0;
	int item1 = 0, item2 = 0, item3 = 0;
	ULONGLONG Playing_time_start = 0;
public:
	HUD() {}
	static HUD* GetInstance()
	{
		if (__instance == NULL) __instance = new HUD();
		return __instance;
	}
	void Render();
	void DrawNumber(int number, float x, float y);
	void DrawPowerMeter(int number, float x, float y);
	void DrawItem(int item, float x, float y);
	void Get1Coin() { this->coin++; }
	void SetPoint(int point) { this->point = point; }
	void SetHealth(int health) { this->health += health; }
	void SetTime(int time) { this->time = time; }
	void TimeStart() { this->Playing_time_start = GetTickCount64(); }
	void SetItemMenu(int item) { 
		if (item1 == 0)item1 = item; 
		else if(item2 == 0)item2 = item;
		else if (item3 == 0)item3 = item;
	}
};

