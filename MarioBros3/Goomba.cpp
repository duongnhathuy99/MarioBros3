#include "Goomba.h"
#include "AssetIDs.h"
#include "PlayScene.h"
CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->vx = -GOOMBA_WALKING_SPEED;
	die_start = -1;
	this->type = type;
	health= HEALTH_GOOMBA;

	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if(state == GOOMBA_STATE_WALKING)
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	LPGAME game = CGame::GetInstance();
	if (game->getIDcurrentScene() == ID_PLAY_SCENE) {
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->IsLevelChange())return;
	}
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId;
	if(vx==0)
		aniId = ID_ANI_GOOMBA_IDLE;
	else
		aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_DIE_OVERTURNED)
	{
		aniId = ID_ANI_GOOMBA_OVERTURNED;
	}		

	if (type == 1) aniId += ID_ANI_GOOMBA_RED;
	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			//vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_DIE_OVERTURNED:
			health = 0;
			vx = 0;
			vy -= GOOMBA_DIE_OVERTURNED_DEFLECT_Y;
			break;
		default:
			break;
	}
}

void CGoomba::TakeDamage() {
	health--;
	if (health == 1)
		SetState(GOOMBA_STATE_WALKING);
	else if (health == 0)
		SetState(GOOMBA_STATE_DIE);
}
