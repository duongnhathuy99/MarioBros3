#pragma once

#define ID_SPRITE_HUB_BOARD 65000
#define ID_SPRITE_HUB_BACKGROUND 65001

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
#define ID_SPRITE_MUSHROOM 65025

#define DISTANCE_HUB_HEIGHT 24
class HUB
{
	//float x, y;
public:
	//HUB(float x, float y) { this->x = x; this->y = y;}
	HUB() {}
	void Render();
	void DrawNumber(int number, float x, float y);
	void DrawPowerMeter(int number, float x, float y);
	void DrawItem();
};

