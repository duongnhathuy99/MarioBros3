#include "BlackKoopa.h"

CBlackKoopa::CBlackKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = BLACK_KOOPA_GRAVITY;
	SetState(BLACK_KOOPA_STATE_SHELL);
}

void CBlackKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BLACK_KOOPA_BBOX_WIDTH / 2;
	top = y - BLACK_KOOPA_BBOX_HEIGHT / 2;
	right = left + BLACK_KOOPA_BBOX_WIDTH;
	bottom = top + BLACK_KOOPA_BBOX_HEIGHT;
}

void CBlackKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBlackKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = - vy / 1.5f ;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CBlackKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBlackKoopa::Render()
{
	int aniId = ID_ANI_BLACK_KOOPA;
	if (state == BLACK_KOOPA_STATE_OVERTURNED)
		aniId = ID_ANI_BLACK_KOOPA_OVERTURNED;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBlackKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACK_KOOPA_STATE_SHELL:
		vx = 0;
		vy = 0;
		break;
	case BLACK_KOOPA_STATE_OVERTURNED:
		vx = 0;
		vy = -BLACK_KOOPA_DIE_OVERTURNED_DEFLECT_Y;
		break;
	}
}