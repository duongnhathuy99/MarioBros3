#include "Star.h"

CStar::CStar(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = STAR_GRAVITY;
}

void CStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - STAR_BBOX_WIDTH / 2;
	top = y - STAR_BBOX_HEIGHT / 2;
	right = left + STAR_BBOX_WIDTH;
	bottom = top + STAR_BBOX_HEIGHT;
}

void CStar::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CStar::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = -STAR_JUMP_SPEED;
		vx = STAR_WALKING_SPEED;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CStar::Render()
{
	int aniId = ID_ANI_STAR;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

