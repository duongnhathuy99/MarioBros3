#pragma once
#include "GameObject.h"

#define PSWITCHES_BBOX 16
#define ID_ANI_PSWITCHES 9011
#define ID_ANI_PSWITCHES_PRESSED 9012

#define PSWITCHES_STATE_INITIAL 1
#define PSWITCHES_STATE_PRESS 2

class PSwitches : public CGameObject {
	bool isPressed;
public:
	PSwitches(float x, float y) : CGameObject(x, y) { 
		isPressed = false; 
		state = PSWITCHES_STATE_INITIAL;
	}
	int IsBlocking() {
		if (isPressed) 	return 0;
		else return 1;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};
