#include "Brick.h"
#include "PSwitches.h"

#include "PlayScene.h"
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(state== BRICK_STATE_INITIAL)
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	else
		animations->Get(ID_ANI_BRICK_UNBOX)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state) {
	CGameObject::SetState(state);
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	switch (state)
	{
	case BRICK_STATE_UNBOX:
		if (item == 1) {
			PSwitches* switches = new PSwitches(x, y - 16);
			scene->AddObject(switches);
		}
		else Delete();
	break; 
	}
}