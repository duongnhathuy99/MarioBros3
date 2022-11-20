#pragma once
#include "GameObject.h"
#define KOOPA_GRAVITY 0.0005f
//#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_OVERTURNE_SPEED_Y 0.1f

#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_SHELL_HEIGHT 14
#define KOOPA_BBOX_SHELL_WIDTH 16

#define KOOPA_SHELL_TIMEOUT 6000
#define KOOPA_RETURN_WALKING_TIME 3000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_SHELL_SPIN 300
#define KOOPA_STATE_HELD_BY 400
#define KOOPA_STATE_SHELL_OVERTURNED 500 

#define ID_ANI_KOOPA_WALKING_LEFT 9001
#define ID_ANI_KOOPA_WALKING_RIGHT 9002
#define ID_ANI_KOOPA_SHELL 9003
#define ID_ANI_KOOPA_RETURN_WALKING 9004
#define ID_ANI_KOOPA_SHELL_SPIN 9005

#define ID_ANI_KOOPA_OVERTURNED_WALKING_LEFT 9006
#define ID_ANI_KOOPA_OVERTURNED_WALKING_RIGHT 9007
#define ID_ANI_KOOPA_OVERTURNED_SHELL 9008
#define ID_ANI_KOOPA_OVERTURNED_RETURN_WALKING 9009
#define ID_ANI_KOOPA_OVERTURNED_SHELL_SPIN 90010
#define ID_ANI_KOOPA_RED 10

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	BOOLEAN isHeldBy;
	ULONGLONG shell_start;
	int type;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		if (state == KOOPA_STATE_SHELL_OVERTURNED) return 0;
		else if (state == KOOPA_STATE_HELD_BY) return 2;
		else return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWitSemiSolidPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y, int type) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		shell_start = -1;
		SetState(KOOPA_STATE_WALKING);
		isHeldBy=false;
		this->type = type;
	};
	virtual void SetState(int state);
};

