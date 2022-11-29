#pragma once
#include "Koopa.h"
#define PARAKOOPA_SPEED_JUMP 0.25f

#define ID_ANI_WING_LEFT 5402
#define ID_ANI_WING_RIGHT 5401

class CParakoopa : public CKoopa
{
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();
public:
	void SetState(int state);
	CParakoopa(float x, float y, int type) :CKoopa(x, y, type) {
		SetState(PARAKOOPA_STATE_JUMP);
		vx = -KOOPA_WALKING_SPEED;
	};
};

