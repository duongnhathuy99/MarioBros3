#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 9010
#define ID_ANI_BRICK_UNBOX 9001
#define ID_ANI_BRICK_COIN 7007

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_INITIAL 1
#define BRICK_STATE_UNBOX 2
#define BRICK_STATE_COIN 3

class CBrick : public CGameObject {
	int item;
public:
	CBrick(float x, float y, int Item) : CGameObject(x, y) { 
		item = Item;
		state = BRICK_STATE_INITIAL; 
	}
	int IsBlocking() {
		if (state == BRICK_STATE_COIN) 	return 0;
		else return 1;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};