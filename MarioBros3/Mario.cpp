#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Koopa.h"
#include "PiranhaPlant.h"
#include "Fireball.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;	
		untouchable = 0;
	}
	//time mario kick
	if (GetTickCount64() - kick_start > MARIO_KICK_TIME)
	{
		kick_start = 0;
		isKick = false;
	}
	
	isOnPlatform = false;
	DebugOutTitle(L"count object:%d", coObjects->size());
	CCollision::GetInstance()->Process(this, dt, coObjects);
	handleTail(dt);
	handleHoldKoopa();
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireball(e);
}
void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e) {
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->ny < 0)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		switch (koopa->GetState())
		{
		case KOOPA_STATE_WALKING:
			koopa->SetState(KOOPA_STATE_SHELL);
			break;
		case KOOPA_STATE_SHELL:
			koopa->SetState(KOOPA_STATE_SHELL_SPIN);
			break;
		case KOOPA_STATE_SHELL_SPIN:
			koopa->SetState(KOOPA_STATE_SHELL);
			break;
		case PARAKOOPA_STATE_JUMP:
			koopa->SetState(KOOPA_STATE_WALKING);
			break;
		}
	}
	else 
	{
		if ( koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_SHELL_SPIN|| koopa->GetState()== PARAKOOPA_STATE_JUMP)
		{
			MarioByAttacked();
		}
		else if (e->nx != 0 && koopa->GetState() == KOOPA_STATE_SHELL)
		{
			if (state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_RUNNING_LEFT) {
				ishold = true;
				holdKoopa = koopa;
				koopa->SetState(KOOPA_STATE_HELD_BY);
			}
			else {
				StartKick();
				koopa->SetState(KOOPA_STATE_SHELL_SPIN);
				if (e->nx < 0)
					koopa->SetSpeed(KOOPA_WALKING_SPEED * 3, 0);
				else if ((e->nx > 0)) koopa->SetSpeed(-KOOPA_WALKING_SPEED * 3, 0);
			}
		}
	}
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		goomba->TakeDamage();
	}
	else // hit by Goomba
	{
		MarioByAttacked();
	}
}
void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranha = dynamic_cast<CPiranhaPlant*>(e->obj);
	MarioByAttacked();
}
void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	MarioByAttacked();
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* quesBrick = (CQuestionBrick*)e->obj;
	if (e->ny > 0)
	{
		if (quesBrick->GetState() == QUESTION_BRICK_STATE_ITEM)
		{
			quesBrick->SetState(QUESTION_BRICK_STATE_MOVEUP);
		}
	}
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(MARIO_LEVEL_BIG);
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(MARIO_LEVEL_RACCOON);
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniId()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (!ishold) {
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if(nx >= 0)
				aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
		}

	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (ishold)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_HOLD_ILDE_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_ILDE_LEFT;
				}
				else 
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (!ishold) {
					if (ax < 0)
						aniId = ID_ANI_MARIO_SKID_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				else if(ax < 0)
					aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
				else
					aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
			}
			else // vx < 0
			{
				if (!ishold) {
					if (ax > 0)
						aniId = ID_ANI_MARIO_SKID_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
				else if (ax > 0)
					aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
			}
	if (isKick) 
	{
		if(nx>0) aniId = ID_ANI_MARIO_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_KICK_LEFT;
	}
	if (isAttack)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_ATTACK_RIGHT;
		else aniId = ID_ANI_MARIO_ATTACK_LEFT;
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniId() + level * DISTANCE_ID_ANI_MARIO;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniId() + level * DISTANCE_ID_ANI_MARIO;
	else if (level == MARIO_LEVEL_FIRE)
		aniId = GetAniId() + level  * DISTANCE_ID_ANI_MARIO;
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniId() + level  * DISTANCE_ID_ANI_MARIO;

	if(level == MARIO_LEVEL_RACCOON )
		if(nx>0 )
			animations->Get(aniId)->Render(x - MARIO_RACCOON_WIDTH_ADJUST, y);
		else
			animations->Get(aniId)->Render(x + MARIO_RACCOON_WIDTH_ADJUST, y);
	else
		animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level!=MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	if (level == l || isAttack) return;
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (l == MARIO_LEVEL_RACCOON) {
		tail = new CTail(x, y + 6);
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(tail);
	}
	if (level == MARIO_LEVEL_RACCOON) {
		tail->Delete();
		tail = NULL;
	}
	level = l;
}
void CMario::MarioByAttacked() {
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_BIG);
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_SMALL);
			StartUntouchable();
		}
		else 
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::handleHoldKoopa() {
	if (ishold) {

		if (holdKoopa->GetState() == KOOPA_STATE_WALKING|| holdKoopa->GetState()== KOOPA_STATE_SHELL_OVERTURNED)
		{
			ishold = false;
		}
		else
		{
			float xKoopa, yKoopa;
			holdKoopa->SetSpeed(vx, vy);
			if (level == MARIO_LEVEL_SMALL)
			{
				yKoopa = y + (MARIO_SMALL_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2;
				if (nx > 0)
					xKoopa = x + (MARIO_SMALL_BBOX_WIDTH + KOOPA_BBOX_SHELL_WIDTH) / 2;
				else
					xKoopa = x - (MARIO_SMALL_BBOX_WIDTH + KOOPA_BBOX_SHELL_WIDTH) / 2;
			}
			else
			{
				if (!isSitting)
				{
					yKoopa = y + (MARIO_BIG_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2;
					if (nx > 0)
						xKoopa = x + (MARIO_BIG_BBOX_WIDTH + KOOPA_BBOX_SHELL_WIDTH) / 2;
					else
						xKoopa = x - (MARIO_BIG_BBOX_WIDTH + KOOPA_BBOX_SHELL_WIDTH) / 2;
				}
				else
				{
					yKoopa = y + (MARIO_BIG_SITTING_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2;
					if (nx > 0)
						xKoopa = x + (MARIO_BIG_BBOX_WIDTH + KOOPA_BBOX_SHELL_WIDTH) / 2;
					else
						xKoopa = x - (MARIO_BIG_BBOX_WIDTH + KOOPA_BBOX_SHELL_WIDTH) / 2;
				}
			}
			holdKoopa->SetPosition(xKoopa, yKoopa);
		}
	}
}
void CMario::releaseHoldKoopa() { 
	if (ishold) {
		StartKick();
		ishold = false;
		holdKoopa->SetState(KOOPA_STATE_SHELL_SPIN);
		if (nx > 0)
			holdKoopa->SetSpeed(KOOPA_WALKING_SPEED * 3, 0);
		else
			holdKoopa->SetSpeed(-KOOPA_WALKING_SPEED * 3, 0);
		holdKoopa = NULL;
	}
}
void CMario::handleTail(DWORD dt) {
	if(level == MARIO_LEVEL_RACCOON)
		tail->calculateSpeed(dt, x - 16 * nx, y + 6);
	if (isAttack) {
		float tail_x, tail_y;
		tail_y = y + 6;
		tail_x = x;
		if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME)
		{
			tail->SetState(TAIL_STATE_ATTACK_INEFFICIENT);
			attack_start = 0;
			isAttack = false;
			return;
		}
		else if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME * 3 / 4)
		{
			tail->SetState(TAIL_STATE_ATTACK_FRONT);
			tail_x = x - 16 * nx;
		}
		else if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME * 2 / 4)
		{
			tail->SetState(TAIL_STATE_ATTACK_INEFFICIENT);
			tail_x = x;
		}
		else if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME * 1 / 4)
		{
			tail->SetState(TAIL_STATE_ATTACK_BACK);
			tail_x = x - 16 * (-nx);
		}
		tail->calculateSpeed(dt, tail_x, tail_y);
	}
}
void CMario::tailAttack() {
	if (!isAttack && level== MARIO_LEVEL_RACCOON) {
		isAttack = true;
		attack_start = GetTickCount64();
	}
}

