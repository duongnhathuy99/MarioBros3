#include "FirePiranhaPlant.h"
#include "Fireball.h"
#include "PlayScene.h"

void CFirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_PRIRANHA_STOP && y < startY && (GetTickCount64() - timestop_start > PRIRANHA_STOP_TIMEOUT/2) && isfire)
	{
		ShootFireball();
	}
	CPiranhaPlant::Update(dt, coObjects);
}
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
	//RenderBoundingBox();
}
void CFirePiranhaPlant::SetState(int state)
{
	if (state == STATE_PRIRANHA_UP) isfire = true;
	CPiranhaPlant::SetState(state);
}
void CFirePiranhaPlant::ShootFireball()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CFireball* fireball = new CFireball(x, y);
	fireball->SetState(FIREBALL_STATE_PIRANHA);
	float mario_x, mario_y, a;
	scene->GetPlayer()->GetPosition(mario_x, mario_y);
	a = (mario_y - y) / (mario_x - x);  
	if (mario_x < x)
		fireball->SetSpeed(-FIREBALL_SPEED, -a * FIREBALL_SPEED);
	else fireball->SetSpeed(FIREBALL_SPEED, a * FIREBALL_SPEED);
	scene->AddObject(fireball);
	isfire = false;
}