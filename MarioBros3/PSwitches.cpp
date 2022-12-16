#include "PSwitches.h"
void PSwitches::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (isPressed)
	{
		animations->Get(ID_ANI_PSWITCHES)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_PSWITCHES)->Render(x, y);
	//RenderBoundingBox();
}

void PSwitches::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PSWITCHES_BBOX / 2;
	t = y - PSWITCHES_BBOX / 2;
	r = l + PSWITCHES_BBOX;
	b = t + PSWITCHES_BBOX;
}

void PSwitches::SetState(int state) {
	CGameObject::SetState(state);
}

void PSwitches::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
};