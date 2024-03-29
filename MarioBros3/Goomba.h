#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.0005f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_DIE_OVERTURNED_DEFLECT_Y 0.1f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DIE_OVERTURNED 300
#define ID_ANI_GOOMBA_WALKING 7100
#define ID_ANI_GOOMBA_DIE 7101
#define ID_ANI_GOOMBA_OVERTURNED 7102
#define ID_ANI_GOOMBA_IDLE 7103
#define ID_ANI_GOOMBA_RED 10
#define HEALTH_GOOMBA 1

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;
	int type;
	int health;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { 
		if (state == GOOMBA_STATE_DIE_OVERTURNED) return 0;
		else return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
public: 	
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);
	void TakeDamage();
};