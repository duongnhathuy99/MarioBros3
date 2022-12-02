#include "Leaf.h"
#include "Debug.h"

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_GRAVITY;
	SetState(LEAF_STATE_FLY_UP);
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - LEAF_BBOX_WIDTH / 2;
		top = y - LEAF_BBOX_HEIGHT / 2;
		right = left + LEAF_BBOX_WIDTH;
		bottom = top + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state== LEAF_STATE_FLY_UP && (GetTickCount64() - flyUp_start > LEAF_FLY_UP_TIME))
	{
		SetState(LEAF_STATE_FALL);
		vx = LEAF_SPEED;
	}
	else if (state == LEAF_STATE_FALL && (GetTickCount64() - fallReverse_start > LEAF_BLOW_UP_TIME))
	{
		SetState(LEAF_STATE_BLOW_UP);
	}
	else if (state == LEAF_STATE_BLOW_UP && (GetTickCount64() - fallReverse_start > LEAF_FALL_REVERSE_TIME))
	{
		SetState(LEAF_STATE_FALL);
	}

	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_RIGHT;
	if (vx < 0)
		aniId = ID_ANI_LEAF_LEFT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_FLY_UP:
		vx = 0;
		vy = -LEAF_SPEED_Y;
		flyUp_start = GetTickCount64();
		break;
	case LEAF_STATE_FALL:
		fallReverse_start = GetTickCount64();
		ay = LEAF_GRAVITY;
		vx = -vx;
		vy = LEAF_SPEED_Y/4;
		break;
	case LEAF_STATE_BLOW_UP:
		ay = -LEAF_GRAVITY*3;
		break;
	}
}
