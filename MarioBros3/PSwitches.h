#pragma once
#include "GameObject.h"

#define PSWITCHES_BBOX 16
#define ID_ANI_PSWITCHES 10001

class PSwitches : public CGameObject {
	bool isPressed;
public:
	PSwitches(float x, float y) : CGameObject(x, y) { 
		isPressed = false; 
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};
