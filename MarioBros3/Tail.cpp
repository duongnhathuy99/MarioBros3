#include "Tail.h"
#include "Goomba.h"
#include "QuestionBrick.h"
#include "Koopa.h"
#include "PiranhaPlant.h"
#include "debug.h"

CTail::CTail(float x, float y) :CGameObject(x, y)
{
	SetState(TAIL_STATE_ATTACK_INEFFICIENT);
}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (state == TAIL_STATE_ATTACK_BACK || state == TAIL_STATE_ATTACK_FRONT)
		goomba->SetState(GOOMBA_STATE_OVERTURNED);
}
void CTail::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questBrick = dynamic_cast<CQuestionBrick*>(e->obj);

	if (state == TAIL_STATE_ATTACK_BACK && questBrick->GetState() == QUESTION_BRICK_STATE_ITEM)
		questBrick->SetState(QUESTION_BRICK_STATE_MOVEUP);
}
void CTail::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (state == TAIL_STATE_ATTACK_BACK || state == TAIL_STATE_ATTACK_FRONT)
		koopa->SetState(KOOPA_STATE_SHELL_OVERTURNED);
}
void CTail::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranha = dynamic_cast<CPiranhaPlant*>(e->obj);
	if (state == TAIL_STATE_ATTACK_BACK || state == TAIL_STATE_ATTACK_FRONT)
		piranha->Delete();
}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTail::Render()
{
	RenderBoundingBox();
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TAIL_STATE_ATTACK_BACK:
		break;
	case TAIL_STATE_ATTACK_FRONT:
		break;
	case TAIL_STATE_ATTACK_INEFFICIENT:
		break;
	}
}
void CTail::calculateSpeed(DWORD dt, float xNext, float yNext) {
	vx = (xNext - x) / dt;
	vy = (yNext - y) / dt;
}