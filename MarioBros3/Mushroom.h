#pragma once
#include "GameObject.h"
#define MUSHROOM_GRAVITY 0.0007f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_GROWUP 200

//#define SPEED_MUSHROOM 0.0002f
#define ID_ANI_MUSHROOM_WALKING 7004
#define ID_ANI_MUSHROOM_1UP_WALKING 7014

#define TYPE_MUSHROOM 1
#define TYPE_MUSHROOM_1UP 2

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float startY;
	int type;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y, int type);
	virtual void SetState(int state);
	int GetType() { return type; }
};

