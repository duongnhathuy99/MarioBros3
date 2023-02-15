#include "CDoor.h"

void CDoor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - DOOR_BBOX_WIDTH / 2;
	top = y - DOOR_BBOX_WIDTH / 2;
	right = left + DOOR_BBOX_WIDTH;
	bottom = top + DOOR_BBOX_WIDTH;
}

void CDoor::OnNoCollision(DWORD dt)
{
	
};

void CDoor::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CDoor::Render()
{
	//int aniId = ID_ANI_MUSHROOM_WALKING;

	//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CDoor::SetState(int state)
{
	CGameObject::SetState(state);
	
}
