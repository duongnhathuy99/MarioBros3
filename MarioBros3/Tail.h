#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 12
#define TAIL_BBOX_HEIGHT 12

#define TAIL_STATE_ATTACK_FRONT 100
#define TAIL_STATE_ATTACK_BACK 200
#define TAIL_STATE_ATTACK_INEFFICIENT 300

class CTail : public CGameObject
{
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	int TypeObject() { return 1; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y);
	void SetState(int state);
	void calculateSpeed(DWORD dt, float xNext,float yNext);
};
