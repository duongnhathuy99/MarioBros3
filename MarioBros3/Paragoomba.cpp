#include "Paragoomba.h"
#include "debug.h"

void CParagoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - wingOpen_start > PARAGOOMBA_WING_OPEN_TIMEOUT)
		isWingOpen = true;
	else
		isWingOpen = false;
	CGoomba::Update(dt, coObjects);
}
void  CParagoomba::OnCollisionWith(LPCOLLISIONEVENT e) {
	CGoomba::OnCollisionWith(e);
	if ((e->ny < 0) && e->obj->IsBlocking() && health == HEALTH_PARAGOOMBA)
	{
		wingOpen_start= GetTickCount64();
		if (GetTickCount64() - walk_start > PARAGOOMBA_WALK_TIMEOUT)
		{
			if (countJump == 3) {
				SetState(PARAGOOMBA_STATE_JUMP_HIGHT);
			}
			else if (countJump == -1)
			{
				walk_start = GetTickCount64();
				countJump = 0;
			}
			else
				SetState(PARAGOOMBA_STATE_JUMP);
		}
	}
}
void CParagoomba::Render()
{
	if (isWingOpen && health == HEALTH_PARAGOOMBA) {
		CAnimations::GetInstance()->Get(ID_ANI_WING_OPEN_LEFT)->Render(x - 5, y - 8);
		CAnimations::GetInstance()->Get(ID_ANI_WING_OPEN_RIGHT)->Render(x + 5, y - 8);
	}
	CGoomba::Render();
	if (!isWingOpen && health == HEALTH_PARAGOOMBA) {
		CAnimations::GetInstance()->Get(ID_ANI_WING_CLOSE_LEFT)->Render(x - 5, y - 6);
		CAnimations::GetInstance()->Get(ID_ANI_WING_CLOSE_RIGHT)->Render(x + 5, y - 6);
	}
}
void CParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health == HEALTH_PARAGOOMBA)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y -  PARAGOOMBA_BBOX_HEIGHT  / 2-(PARAGOOMBA_BBOX_HEIGHT- GOOMBA_BBOX_HEIGHT)/2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
	else 
		CGoomba::GetBoundingBox(left,  top,  right, bottom);
}
void CParagoomba::SetState(int state)
{
	switch (state)
	{
	case PARAGOOMBA_STATE_JUMP:
		vy = -PARAGOOMBA_SPEED_JUMP ;
		countJump++;
		break;
	case PARAGOOMBA_STATE_JUMP_HIGHT:
		vy = -PARAGOOMBA_SPEED_JUMP*3 ;
		countJump=-1;
		break;
	}
	CGoomba::SetState(state);
}