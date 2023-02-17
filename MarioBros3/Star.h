#pragma once

#include "GameObject.h"
#define STAR_GRAVITY 0.0007f
#define STAR_WALKING_SPEED 0.05f
#define STAR_JUMP_SPEED 0.3f

#define STAR_BBOX_WIDTH 16
#define STAR_BBOX_HEIGHT 14

#define ID_ANI_STAR 7008

class CStar : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CStar(float x, float y);
};

