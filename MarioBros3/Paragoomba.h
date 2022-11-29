#pragma once
#include "Goomba.h"
#define PARAGOOMBA_BBOX_WIDTH 20
#define PARAGOOMBA_BBOX_HEIGHT 24
#define PARAGOOMBA_SPEED_JUMP 0.08f
#define PARAGOOMBA_WALK_TIMEOUT 1500
#define PARAGOOMBA_WING_OPEN_TIMEOUT 200

#define PARAGOOMBA_STATE_WALK 400
#define PARAGOOMBA_STATE_JUMP 500
#define PARAGOOMBA_STATE_JUMP_HIGHT 600

#define ID_ANI_WING_OPEN_LEFT 5403
#define ID_ANI_WING_OPEN_RIGHT 5404
#define ID_ANI_WING_CLOSE_LEFT 5405
#define ID_ANI_WING_CLOSE_RIGHT 5406

#define HEALTH_PARAGOOMBA 2
class CParagoomba : public CGoomba
{
	BOOLEAN isWingOpen;
	ULONGLONG walk_start;
	ULONGLONG wingOpen_start;
	int countJump;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();
public:
	CParagoomba(float x, float y, int type) :CGoomba(x, y, type) {
		walk_start = GetTickCount64();
		wingOpen_start = 0;
		countJump = 0;
		health = HEALTH_PARAGOOMBA;
		isWingOpen = false;
		state = GOOMBA_STATE_WALKING;
	};
	void SetState(int state);
};

