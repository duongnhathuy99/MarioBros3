#pragma once
#include "PiranhaPlant.h"

#define ID_ANI_PRIRANHA_GREEN_DOWN_LEFT 7303
#define ID_ANI_PRIRANHA_GREEN_UP_LEFT 7304
#define ID_ANI_PRIRANHA_GREEN_DOWN_RIGHT 7305
#define ID_ANI_PRIRANHA_GREEN_UP_RIGHT 7306
class CFirePiranhaPlant :public CPiranhaPlant
{
	BOOLEAN isfire=false;
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void ShootFireball();
public:
	CFirePiranhaPlant(float x, float y, int stem, int Color) :CPiranhaPlant(x, y, stem, Color) { };
	void SetState(int state);
};

