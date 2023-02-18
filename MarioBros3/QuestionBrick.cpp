#include "QuestionBrick.h"
#include "Mario.h"
void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(questionBrick_unbox)
	{
		animations->Get(ID_ANI_BRICK_UNBOX)->Render(x, y);
		//coin->Render();
	}
	else
		animations->Get(ID_ANI_BRICK_ITEM)->Render(x, y);
	//RenderBoundingBox();
	
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX / 2;
	t = y - BRICK_BBOX / 2;
	r = l + BRICK_BBOX;
	b = t + BRICK_BBOX;
}

void CQuestionBrick::SetState(int state) {
	CGameObject::SetState(state);
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	switch (state)
	{
	case QUESTION_BRICK_STATE_ITEM:
		vy = 0;
		break;
	case QUESTION_BRICK_STATE_MOVEUP:
		vy = -SPEED_QUESTION_BRICK;
		questionBrick_unbox = true;
		if (item == ITEM_COIN) {
			CCoin* coin = new CCoin(x, y - BRICK_BBOX);
			coin->SetState(COIN_STATE_MOVEUP);
			scene->AddObject(coin);
		}
		if (item == ITEM_LEVEL_UP && mario->GetLevel() >= MARIO_LEVEL_BIG) {
			CLeaf* leaf = new CLeaf(x, y);
			scene->AddObject(leaf);
		}
		break;
	case QUESTION_BRICK_STATE_MOVEDOWN:
		vy = SPEED_QUESTION_BRICK;
		break;
	case QUESTION_BRICK_STATE_UNBOX:
		if (item == ITEM_LEVEL_UP && mario->GetLevel() == MARIO_LEVEL_SMALL) {
			CMushroom* mushroom = new CMushroom(x, y ,TYPE_MUSHROOM);
			mushroom->SetState(MUSHROOM_STATE_GROWUP);
			scene->AddObject(mushroom);
		}
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
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
};