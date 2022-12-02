#pragma once
#include "GameObject.h"
#define LEAF_GRAVITY 0.0001f
#define LEAF_SPEED_Y 0.11f
#define LEAF_SPEED 0.05f

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_STATE_BLOW_UP 100
#define LEAF_STATE_FALL 200
#define LEAF_STATE_FLY_UP 300

#define ID_ANI_LEAF_RIGHT 7001
#define ID_ANI_LEAF_LEFT 7002

#define LEAF_FLY_UP_TIME 1500
#define LEAF_FALL_REVERSE_TIME 800
#define LEAF_BLOW_UP_TIME LEAF_FALL_REVERSE_TIME/2

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG flyUp_start;
	ULONGLONG fallReverse_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};