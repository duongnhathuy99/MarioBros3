#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_IDLE 1
#define COIN_STATE_MOVEUP 2
#define COIN_STATE_MOVEDOWN 3
#define COIN_STATE_POINT 4

#define DISTANCE_COIN_MOVEUP 64
#define DISTANCE_COIN_MOVEDOWN 16
#define SPEED_COIN 0.18f
class CCoin : public CGameObject {
	float startY;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		state = COIN_STATE_IDLE;
		startY=y;
	}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int state);
};