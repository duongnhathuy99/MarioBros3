#include "Koopa.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	shell_start = -1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_WALKING)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else 
	{
		left = x - KOOPA_BBOX_SHELL_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_SHELL_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_SHELL) && (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId= ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_WALKING )
	{
		if(vx<0) aniId = ID_ANI_KOOPA_WALKING_LEFT;
		else aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if(state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
		if(GetTickCount64() - shell_start > KOOPA_RETURN_WALKING_TIME)
			aniId = ID_ANI_KOOPA_RETURN_WALKING;
	}
	else if (state == KOOPA_STATE_SHELL_SPIN)
	{
		aniId = ID_ANI_KOOPA_SHELL_SPIN;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2;
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_SPIN:
		vx = -KOOPA_WALKING_SPEED*2;
		break;
	}
}
