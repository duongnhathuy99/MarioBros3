#pragma once
#include "GameObject.h"
#define BLACK_KOOPA_GRAVITY 0.0007f
#define BLACK_KOOPA_DIE_OVERTURNED_DEFLECT_Y 0.1f

#define BLACK_KOOPA_BBOX_WIDTH 16
#define BLACK_KOOPA_BBOX_HEIGHT 14
#define BLACK_KOOPA_STATE_SHELL 1
#define BLACK_KOOPA_STATE_OVERTURNED 2

#define ID_ANI_BLACK_KOOPA 7410
#define ID_ANI_BLACK_KOOPA_OVERTURNED 7411
class CBlackKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		if (state == BLACK_KOOPA_STATE_OVERTURNED) return 0;
		else return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBlackKoopa(float x, float y);
	void SetState(int state);
};

