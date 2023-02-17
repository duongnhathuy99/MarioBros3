#pragma once
#include "GameObject.h"
#define KOOPA_GRAVITY 0.0008f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_DIE_OVERTURNED_DEFLECT_Y 0.15f
#define KOOPA_OVERTURNED_DEFLECT_Y 0.28f
#define KOOPA_OVERTURNED_DEFLECT_X 0.07f

#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_SHELL_HEIGHT 14
#define KOOPA_BBOX_SHELL_WIDTH 16

#define KOOPA_SHELL_TIMEOUT 8000
#define KOOPA_RETURN_WALKING_TIME 6000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_SHELL_SPIN 300
#define KOOPA_STATE_HELD_BY 400
#define KOOPA_STATE_DIE_SHELL_OVERTURNED 500 
#define PARAKOOPA_STATE_JUMP 600 

#define ID_ANI_KOOPA_WALKING_LEFT 7201
#define ID_ANI_KOOPA_WALKING_RIGHT 7202
#define ID_ANI_KOOPA_SHELL 7203
#define ID_ANI_KOOPA_RETURN_WALKING 7204
#define ID_ANI_KOOPA_SHELL_SPIN 7205

#define ID_ANI_KOOPA_OVERTURNED_SHELL 7208
#define ID_ANI_KOOPA_OVERTURNED_RETURN_WALKING 7209
#define ID_ANI_KOOPA_OVERTURNED_SHELL_SPIN 7210

#define ID_ANI_KOOPA_RED 10

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	BOOLEAN isOnPlatform;
	BOOLEAN isHeldBy;
	BOOLEAN isOverturned;
	ULONGLONG shell_start;
	int type;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		if (state == KOOPA_STATE_DIE_SHELL_OVERTURNED) return 0;
		else if (state == KOOPA_STATE_HELD_BY) return 2;
		else return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBlackKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y, int type) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		this->isOnPlatform = false;
		shell_start = -1;
		SetState(KOOPA_STATE_WALKING);
		this->isHeldBy = false;
		this->isOverturned = false;
		this->type = type;
	};
	virtual void SetState(int state);
	void AttackedByTail() {
		isOverturned = true;  
		SetState(KOOPA_STATE_SHELL); 
		//vy -= KOOPA_OVERTURNED_SPEED_Y;
	}
};

