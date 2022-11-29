#include "Parakoopa.h"

//void CParakoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	
//	CKoopa::Update(dt, coObjects);
//}
void  CParakoopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	CKoopa::OnCollisionWith(e);
	if ((e->ny < 0) && e->obj->IsBlocking() && state == PARAKOOPA_STATE_JUMP)
	{
		SetState(PARAKOOPA_STATE_JUMP);
	}
}
void CParakoopa::Render()
{
	CKoopa::Render();
	if (state == PARAKOOPA_STATE_JUMP) {
		if(vx<0)
			CAnimations::GetInstance()->Get(ID_ANI_WING_LEFT)->Render(x + 5, y - 8);
		else
			CAnimations::GetInstance()->Get(ID_ANI_WING_RIGHT)->Render(x - 5, y - 8);
	}
}
void CParakoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*if (state == KOOPA_STATE_JUMP)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2 - (PARAGOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT) / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
	else*/
		CKoopa::GetBoundingBox(left, top, right, bottom);
}
void CParakoopa::SetState(int state)
{
	switch (state)
	{
	case PARAKOOPA_STATE_JUMP:
		vy = -PARAKOOPA_SPEED_JUMP;
		break;
	}
	CKoopa::SetState(state);
}