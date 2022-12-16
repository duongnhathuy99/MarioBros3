#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_UNBOX 6001
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_INITIAL 1
#define BRICK_STATE_UNBOX 2

class CBrick : public CGameObject {
	int item;
public:
	CBrick(float x, float y, int Item) : CGameObject(x, y) { 
		item = Item;
		state = BRICK_STATE_INITIAL; 
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};