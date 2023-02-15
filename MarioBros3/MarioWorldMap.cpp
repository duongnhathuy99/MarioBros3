#include <algorithm>
#include "debug.h"

#include "MarioWorldMap.h"
#include "Game.h"

void MarioWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOutTitle(L"x:%f   y:%f  value:%d  left:%d   top:%d   right:%d   bot:%d", x-8, y-8, door->GetType(), door->GetLeft(), door->GetTop(), door->GetRight(), door->GetBot());
	if ( (abs(x_start - x) >= MARIO_WORLD_DISTANCE_CAN_GO || abs(y_start - y) >= MARIO_WORLD_DISTANCE_CAN_GO) && state != MARIO_WORLD_STATE_IDLE)
	{
		if (vx != 0)
			if (vx < 0) x = x_start - MARIO_WORLD_DISTANCE_CAN_GO;
			else x = x_start + MARIO_WORLD_DISTANCE_CAN_GO;
		else
			if (vy < 0) y = y_start - MARIO_WORLD_DISTANCE_CAN_GO;
			else y = y_start + MARIO_WORLD_DISTANCE_CAN_GO;
		SetState(MARIO_WORLD_STATE_IDLE);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void MarioWorldMap::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void MarioWorldMap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if ((e->ny != 0 || e->nx != 0)&& e->obj->IsBlocking())
	{
		SetState(MARIO_WORLD_STATE_IDLE);
	}
	if (dynamic_cast<CDoor*>(e->obj))
		door = dynamic_cast<CDoor*>(e->obj);
}

//
// Get animdation ID for big Mario
//

void MarioWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_MARIO_WORLD_SMALL;
	animations->Get(aniId)->Render(x - MARIO_WORLD_BBOX_WIDTH_ADJUST, y - MARIO_WORLD_BBOX_HEIGHT_ADJUST);
	RenderBoundingBox();
}

void MarioWorldMap::SetState(int state)
{
	
	switch (state)
	{
	case MARIO_WORLD_STATE_GO_UP:
		if (!door->GetTop()) return;
		vy = -MARIO_WORLD_SPEED;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_GO_DOWN:
		if (!door->GetBot()) return;
		vy = MARIO_WORLD_SPEED;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_GO_LEFT:
		if (!door->GetLeft()) return;
		vx = -MARIO_WORLD_SPEED;
		vy = 0;
		break;
	case MARIO_WORLD_STATE_GO_RIGHT:
		if (!door->GetRight()) return;
		vx = MARIO_WORLD_SPEED;
		vy = 0;
		break;
	case MARIO_WORLD_STATE_IDLE:
		vx = 0;
		vy = 0;
		x_start = x;
		y_start = y;
		break;
	}
	CGameObject::SetState(state);
}

void MarioWorldMap::StartPlayScene() {
	if (state != MARIO_WORLD_STATE_IDLE) return;
	if(door->GetType() == DOOR_TYPE_1) CGame::GetInstance()->InitiateSwitchScene(2);
}
void MarioWorldMap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	left = x - MARIO_WORLD_BBOX / 2;
	top = y - MARIO_WORLD_BBOX / 2;
	right = left + MARIO_WORLD_BBOX;
	bottom = top + MARIO_WORLD_BBOX;
	
}