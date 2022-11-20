#include "Koopa.h"
#include "debug.h"

#include "SemisolidPlatform.h"
#include "Goomba.h"
#include "QuestionBrick.h"
#include "Koopa.h"

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
	if (state == KOOPA_STATE_HELD_BY)return;
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())
	{
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	if (dynamic_cast<CSemisolidPlatform*>(e->obj) )
	{
		OnCollisionWitSemiSolidPlatform(e);
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
}
void CKoopa::OnCollisionWitSemiSolidPlatform(LPCOLLISIONEVENT e)
{
	if ((e->ny < 0) && state == KOOPA_STATE_WALKING && type==1)
	{
		float l, t, r, b;
		e->obj->GetBoundingBox(l, t, r, b);
		if (x < l)
		{
			x = l;
			vx = -vx;
		}
		if (x > r)
		{
			x = r;
			vx = -vx;
		}
	}
}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPA_STATE_HELD_BY)
	{
		SetState(KOOPA_STATE_SHELL_OVERTURNED);
		goomba->SetState(GOOMBA_STATE_OVERTURNED);
	}
	else if ((e->nx != 0) && state == KOOPA_STATE_SHELL_SPIN)
	{
		goomba->SetState(GOOMBA_STATE_OVERTURNED);
	}
}
void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questBrick = dynamic_cast<CQuestionBrick*>(e->obj);

	if ((e->nx != 0) && state == KOOPA_STATE_SHELL_SPIN)
	{
		questBrick->SetState(QUESTION_BRICK_STATE_MOVEUP);
	}
}
void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (state == KOOPA_STATE_HELD_BY)
	{
		SetState(KOOPA_STATE_SHELL_OVERTURNED);
		koopa->SetState(KOOPA_STATE_SHELL_OVERTURNED);
	}
	else if ((e->nx != 0) && (state == KOOPA_STATE_SHELL_SPIN))
	{
		koopa->SetState(KOOPA_STATE_SHELL_OVERTURNED);
	}
}
void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if ((state == KOOPA_STATE_SHELL||state == KOOPA_STATE_HELD_BY) && (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT))
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
	else if(state == KOOPA_STATE_SHELL|| state == KOOPA_STATE_HELD_BY)
	{
		aniId = ID_ANI_KOOPA_SHELL;
		if(GetTickCount64() - shell_start > KOOPA_RETURN_WALKING_TIME)
			aniId = ID_ANI_KOOPA_RETURN_WALKING;
	}
	else if (state == KOOPA_STATE_SHELL_SPIN)
	{
		aniId = ID_ANI_KOOPA_SHELL_SPIN;
	}
	else if (state == KOOPA_STATE_SHELL_OVERTURNED)
	{
		aniId = ID_ANI_KOOPA_OVERTURNED_SHELL;
	}

	if (type == 1) 
		aniId += ID_ANI_KOOPA_RED;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
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
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_SHELL_SPIN:
		vx = -KOOPA_WALKING_SPEED * 3;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_HELD_BY:
		ay = 0;
		break;
	case KOOPA_STATE_SHELL_OVERTURNED:
		vx = 0;
		vy -= KOOPA_OVERTURNE_SPEED_Y;
		ay = KOOPA_GRAVITY;
		break;
	}
}
