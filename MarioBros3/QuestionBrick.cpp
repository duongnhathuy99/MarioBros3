#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(questionBrick_unbox)
	{
		animations->Get(ID_ANI_BRICK_UNBOX)->Render(x, y);
		coin->Render();
	}
	else
		animations->Get(ID_ANI_BRICK_ITEM)->Render(x, y);
	RenderBoundingBox();
	
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_STATE_ITEM:
		vy = 0;
		break;
	case QUESTION_BRICK_STATE_MOVEUP:
		vy = -SPEED_QUESTION_BRICK;
		questionBrick_unbox = true;
		coin= new CCoin(x, y - BRICK_BBOX_HEIGHT);
		coin->SetState(COIN_STATE_MOVEUP);
		break;
	case QUESTION_BRICK_STATE_MOVEDOWN:
		vy = SPEED_QUESTION_BRICK;
		break;
	case QUESTION_BRICK_STATE_UNBOX:
		y = startY;
		vy = 0;
		break;
	default:
		break;
	}
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects ) {
	if (startY - y > DISTANCE_QUESTION_BRICK_MOVEUP)
	{
		SetState(QUESTION_BRICK_STATE_MOVEDOWN);
	}
	if (vy > 0 && y >= startY) {
		SetState(QUESTION_BRICK_STATE_UNBOX);
	}
	if (state!= QUESTION_BRICK_STATE_ITEM) {
		coin->Update(dt);
	}
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
};