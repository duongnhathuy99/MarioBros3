#pragma once
#include "GameObject.h"

#define PIRANHA_SPEED 0.02f
#define PIRANHA_BBOX 16
#define STEM_BBOX_WIDTH 16
#define STEM_BBOX_HEIGHT 8

#define PRIRANHA_STOP_TIMEOUT 1700

#define STATE_PRIRANHA_UP 100
#define STATE_PRIRANHA_STOP 200
#define STATE_PRIRANHA_DOWN 300
//#define STATE_PRIRANHA_GREEN_DOWN_LEFT 200
//#define STATE_PRIRANHA_GREEN_UP_LEFT 300

#define ID_ANI_STEM 8000
#define ID_ANI_PRIRANHA_GREEN_UP 8001
#define ID_ANI_PRIRANHA_GREEN_DOWN_LEFT 8002
#define ID_ANI_PRIRANHA_GREEN_UP_LEFT 8003

class CPiranhaPlant : public CGameObject
{
	float ax;
	float ay;
	int stem;
	float startY;
	ULONGLONG timestop_start;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void RenderBoundingBox();
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPiranhaPlant(float x, float y,int stem);
	virtual void SetState(int state);
};

