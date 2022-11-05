#include "PiranhaPlant.h"
#include "Textures.h"
#include "Pipe.h"
#include "debug.h"

CPiranhaPlant::CPiranhaPlant(float x, float y,int Stem) :CGameObject(x, y)
{
	timestop_start = 0;
	startY = y;
	stem = Stem;
	SetState(STATE_PRIRANHA_UP);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - PIRANHA_BBOX / 2;
		top = y - PIRANHA_BBOX / 2;
		right = left + PIRANHA_BBOX;
		bottom = top + PIRANHA_BBOX+STEM_BBOX_HEIGHT*stem;
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

}
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state == STATE_PRIRANHA_UP)&&startY - y > PIRANHA_BBOX+stem*STEM_BBOX_HEIGHT)
	{
		y = startY - (PIRANHA_BBOX + stem * STEM_BBOX_HEIGHT);
		SetState(STATE_PRIRANHA_STOP);
	}
	
	if ((state == STATE_PRIRANHA_STOP) && (GetTickCount64() - timestop_start > PRIRANHA_STOP_TIMEOUT))
	{
		if(y<startY)
			SetState(STATE_PRIRANHA_DOWN);
		else
			SetState(STATE_PRIRANHA_UP);
	}
	if ((state == STATE_PRIRANHA_DOWN) && startY < y )
	{
		y = startY;
		SetState(STATE_PRIRANHA_STOP);
	}
	//DebugOutTitle(L"timestop: %d   vy:%f   y:%f", timestop_start, vy,y);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float yy = y - PIRANHA_BBOX / 2+ STEM_BBOX_HEIGHT*stem / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
void CPiranhaPlant::Render()
{
	
	for(int i=0;i<=stem;i++)
	CAnimations::GetInstance()->Get(ID_ANI_STEM)->Render(x, y+i*STEM_BBOX_HEIGHT+ STEM_BBOX_HEIGHT/2);
	CAnimations::GetInstance()->Get(ID_ANI_PRIRANHA_GREEN_UP)->Render(x, y);
	RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_PRIRANHA_UP:
		vy = -PIRANHA_SPEED;
		timestop_start = 0;
		break;
	case STATE_PRIRANHA_STOP:
		if(timestop_start==0)
		timestop_start = GetTickCount64();
		vy = 0;
		break;
	case STATE_PRIRANHA_DOWN:
		vy = PIRANHA_SPEED;
		timestop_start = 0;
		break;
	
	}
}
