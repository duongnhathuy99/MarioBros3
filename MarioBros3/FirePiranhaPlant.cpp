#include "FirePiranhaPlant.h"
#include "PlayScene.h"
void CFirePiranhaPlant::Render()
{
	int ani;
	for (int i = 1; i <= stem; i++)
		CAnimations::GetInstance()->Get(ID_ANI_STEM)->Render(x, y + i * STEM_BBOX_HEIGHT + STEM_BBOX_HEIGHT / 2);
	LPPLAYSCENE scene=(LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float mario_x, mario_y;
	scene->GetPlayer()->GetPosition(mario_x, mario_y);
	if(mario_y>y)
		if(mario_x > x)
			ani = ID_ANI_PRIRANHA_GREEN_DOWN_RIGHT;
		else
			ani = ID_ANI_PRIRANHA_GREEN_DOWN_LEFT;
	else
		if (mario_x > x)
			ani = ID_ANI_PRIRANHA_GREEN_UP_RIGHT;
		else
			ani = ID_ANI_PRIRANHA_GREEN_UP_LEFT;
	if (state == STATE_PRIRANHA_STOP) ani += 4;
	if (color == 1) ani += 8;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
}
