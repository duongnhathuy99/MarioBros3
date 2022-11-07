#pragma once
#include "PiranhaPlant.h"

#define ID_ANI_PRIRANHA_GREEN_DOWN_LEFT 8003
#define ID_ANI_PRIRANHA_GREEN_UP_LEFT 8004
#define ID_ANI_PRIRANHA_GREEN_DOWN_RIGHT 8005
#define ID_ANI_PRIRANHA_GREEN_UP_RIGHT 8006
class CFirePiranhaPlant :public CPiranhaPlant
{
	void Render();
public:
	CFirePiranhaPlant(float x, float y, int stem, int Color) :CPiranhaPlant(x, y, stem, Color) {};
};

