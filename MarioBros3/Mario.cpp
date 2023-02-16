#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"
#include "HUD.h"
#include "Goomba.h"
#include "Coin.h"
#include "QuestionBrick.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Koopa.h"
#include "PiranhaPlant.h"
#include "Fireball.h"
#include "PSwitches.h"
#include "Pipe.h"
#include "ItemsMenu.h"
#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	//DebugOutTitle(L"vx:%f   vy:%f   nx:%d    state:%d", vx, vy, nx,state);
	if (abs(vx) > abs(maxVx) && vx*maxVx > 0) vx = maxVx;
	if (abs(vy) > maxVy && vy>0) vy = maxVy;
	
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;	
		isUntouchable = false;
	}
	// time level change mario idle
	if (GetTickCount64() - levelChange_start > MARIO_LEVEL_CHANGE_TIME)
	{
		levelChange_start = 0;
		isLevelChange = 0;
	}
	if (isLevelChange)return;
	//time mario press P-Switches
	if (GetTickCount64() - PSwitches_start > PSWITCHES_TIME)
	{
		PSwitches_start = 0;
		isPSwitches = false;
	}
	//time mario kick
	if (GetTickCount64() - kick_start > MARIO_KICK_TIME)
	{
		kick_start = 0;
		isKick = false;
	}
	//time mario slow fall
	if (GetTickCount64() - slowFall_start < MARIO_TAIL_SLOW_FALL_TIME && !isOnPlatform)
	{
		vy = MARIO_SLOW_FALL_SPEED_Y;
		ay = 0;
	}
	else 	ay = MARIO_GRAVITY;
	//time mario fly
	if (GetTickCount64() - fly_start > MARIO_FLY_TIME && isfly)
	{
		isfly = false;
		PowerMeter = 0;
	}
	//mario go in pipe
	if (isGoInPipe)
	{
		ay = 0;
		int mario_bbox;
		if (level != MARIO_LEVEL_SMALL)
			mario_bbox = MARIO_BIG_BBOX_HEIGHT;
		else
			mario_bbox = MARIO_SMALL_BBOX_HEIGHT;
		if (y - startY_GoInpipe > mario_bbox && state == MARIO_STATE_GO_IN_PIPE) {
			if (!isInHiddenMap) {
				if (level != MARIO_LEVEL_SMALL)
					SetPosition(POSITION_GO_DOWN_PIPE_X, POSITION_GO_DOWN_PIPE_Y);
				else
					SetPosition(POSITION_GO_DOWN_PIPE_X, POSITION_GO_DOWN_PIPE_Y + (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2);
				startY_GoInpipe = y;
				isInHiddenMap = true;
			}
			else {
				isGoInPipe = false;
				startY_GoInpipe = 0;
				ay = MARIO_GRAVITY;
			}
		}
		if (startY_GoInpipe - y > mario_bbox && state == MARIO_STATE_GO_IN_PIPE) {
			if (isInHiddenMap) {
				if(level != MARIO_LEVEL_SMALL)
					SetPosition(POSITION_GO_UP_PIPE_X, POSITION_GO_UP_PIPE_Y);
				else
					SetPosition(POSITION_GO_UP_PIPE_X, POSITION_GO_UP_PIPE_Y-(MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT)/2);
				startY_GoInpipe = y;
				isInHiddenMap = false;
			}
			else {
				isGoInPipe = false;
				startY_GoInpipe = 0;
				ay = MARIO_GRAVITY;
			}
		}
	}
	calculatePowerMeter();
	isCollisionWithPipe = 0;
	isOnPlatform = false;
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
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
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
	else if (dynamic_cast<PSwitches*>(e->obj))
		OnCollisionWithPSwitches(e);
	else if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
	else if (dynamic_cast<ItemsMenu*>(e->obj))
		OnCollisionWithItemsMenu(e);
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
		else if (e->nx != 0 && (koopa->GetState() == KOOPA_STATE_SHELL))
		{
			if (state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_RUNNING_LEFT) {
				ishold = true;
				holdKoopa = koopa;
				koopa->SetState(KOOPA_STATE_HELD_BY);
			}
			else {
				StartKick();
				koopa->SetState(KOOPA_STATE_SHELL_SPIN);
				koopa->SetSpeed(-KOOPA_WALKING_SPEED * 3 * e->nx, 0);
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
	HUD::GetInstance()->Get1Coin();
	e->obj->Delete();
}
void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (e->obj->GetState() == BRICK_STATE_COIN) {
		e->obj->Delete();
		HUD::GetInstance()->Get1Coin();
	}else if(e->obj->GetState() == BRICK_STATE_INITIAL && e->ny > 0)
		e->obj->SetState(BRICK_STATE_UNBOX);
	
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
void CMario::OnCollisionWithPSwitches(LPCOLLISIONEVENT e) {
	if (e->ny < 0 && e->obj->GetState() == PSWITCHES_STATE_INITIAL)
	{
		e->obj->SetState(PSWITCHES_STATE_PRESS);
		isPSwitches = true;
		PSwitches_start = GetTickCount64();
	}
}
void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e) {
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	float xPipe, yPipe;
	pipe->GetPosition(xPipe, yPipe);
	if (e->ny != 0 && pipe->IsGoInside() && xPipe - RANGE_GO_IN_PIPE + TILE_BBOX/2 < x && x < xPipe + RANGE_GO_IN_PIPE + TILE_BBOX/2)
	{
		isCollisionWithPipe = (int)e->ny;
	}
}
void CMario::OnCollisionWithItemsMenu(LPCOLLISIONEVENT e) {
	ItemsMenu* items = dynamic_cast<ItemsMenu*>(e->obj);
	items->SetState(ITEMS_MENU_STATE_FLY_UP_SPINNING);
	this->SetState(MARIO_STATE_END_SCENE);
	HUD::GetInstance()->SetItemMenu(items->GetTypeItems());
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
			if (PowerMeter==7)
			{
				if (vy < 0) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_FALL_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_FALL_RUN_LEFT;
				}
			}
			else
			{
				if (vy < 0) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_FALL_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_FALL_WALK_LEFT;
				}
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
					{
						if(state == MARIO_STATE_IDLE)
							aniId = ID_ANI_MARIO_WALKING_RIGHT;
						else
							aniId = ID_ANI_MARIO_SKID_RIGHT;
					}
					else if (vx <= MARIO_WALKING_SPEED)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					else if ( MARIO_WALKING_SPEED < vx && vx < MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_WALKING_FAST_RIGHT;
					else if (vx >= MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
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
					{
						if (state == MARIO_STATE_IDLE)
							aniId = ID_ANI_MARIO_WALKING_LEFT;
						else
							aniId = ID_ANI_MARIO_SKID_LEFT;
					}
					else if (abs(vx) <= MARIO_WALKING_SPEED)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					else if (MARIO_WALKING_SPEED < abs(vx) && abs(vx) < MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_WALKING_FAST_LEFT;
					else if (abs(vx) >= MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
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
		if (tail->GetState() == TAIL_STATE_IDLE_BACK)
			aniId = ID_ANI_MARIO_TAIL_BACK;
		else if (tail->GetState() == TAIL_STATE_IDLE_FRONT)
			aniId = ID_ANI_MARIO_TAIL_FRONT;
		else if (tail->GetState() == TAIL_STATE_ATTACK_BACK)
		{
			if (nx < 0) aniId = ID_ANI_MARIO_ATTACK_RIGHT;
			else aniId = ID_ANI_MARIO_ATTACK_LEFT;
		}
		else if (tail->GetState() == TAIL_STATE_ATTACK_FRONT)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_ATTACK_RIGHT;
			else aniId = ID_ANI_MARIO_ATTACK_LEFT;
		}
	}
	if (isGoInPipe) 
	{
		aniId = ID_ANI_MARIO_TAIL_FRONT;
	}
	if (isLevelChange!=0) {
		if ((level == MARIO_LEVEL_SMALL && isLevelChange > 0) || (level == MARIO_LEVEL_BIG && isLevelChange < 0))
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_TO_BIG_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_TO_BIG_LEFT;
		}
		else
			aniId = ID_ANI_MARIO_EFFECT_SMOKE;
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

	if (level == MARIO_LEVEL_RACCOON)
	{
		if (tail->GetState() == TAIL_STATE_ATTACK_BACK)
			animations->Get(aniId)->Render(x - MARIO_RACCOON_WIDTH_ADJUST * (-nx), y);
		else if ((tail->GetState() == TAIL_STATE_IDLE_BACK || tail->GetState() == TAIL_STATE_IDLE_FRONT) && isAttack)
			animations->Get(aniId)->Render(x, y);
		else
			animations->Get(aniId)->Render(x - MARIO_RACCOON_WIDTH_ADJUST * nx, y);
	}
	else {
		if (!isUntouchable)
			animations->Get(aniId)->Render(x, y);
		else if ((GetTickCount64() - untouchable_start) % 2 == 0)
			animations->Get(aniId)->Render(x, y);
	}
	//RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (isGoInPipe)	return;
	if (this->state == MARIO_STATE_DIE || this->state == MARIO_STATE_END_SCENE) return;
	//DebugOut(L"state: %d \n", state);
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		if (vx < 0) ax = MARIO_ACCEL_RUN_X * 3;
		else
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		if (vx > 0) ax = -MARIO_ACCEL_RUN_X * 3;
		else
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		if (vx < 0) ax = MARIO_ACCEL_WALK_X * 3;
		else
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting)break;
		maxVx = -MARIO_WALKING_SPEED;
		if (vx > 0) ax = -MARIO_ACCEL_WALK_X * 3;
		else
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
		//if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 4;
		if (vy < 0) vy /= 1.6f;
		break;

	case MARIO_STATE_SIT:
		if (ishold || isAttack) break;
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			ax = 0; ay = 0;
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
	case MARIO_STATE_SLOW_FALL:
		if(level==MARIO_LEVEL_RACCOON)
			slowFall_start = GetTickCount64();
		break;
	case MARIO_STATE_IDLE:
		if (vx > 0)
			ax = -MARIO_SLOW_ACCEL_WALK_X;
		else if(vx < 0)
			ax = MARIO_SLOW_ACCEL_WALK_X;
		if (abs(vx) < MARIO_WALKING_SPEED_MIN) {
			vx = 0;
			ax = 0;
		}
		break;
	case MARIO_STATE_FLY:
		if (level == MARIO_LEVEL_RACCOON)
		{
			if(!isfly) fly_start = GetTickCount64();
			isfly = true;
			vy = -MARIO_FLY_SPEED_Y;
		}
		break;
	case MARIO_STATE_GO_IN_PIPE:
		isGoInPipe = true;
		vy = MARIO_GO_IN_PIPE_SPEED_Y * -isCollisionWithPipe;
		vx = 0;
		ax = 0;
		ay = 0;
		startY_GoInpipe = y;
		y -= isCollisionWithPipe;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;	
	case MARIO_STATE_END_SCENE:
		ax = 0;
		vy = 0;
		vx = MARIO_END_SCENE_SPEED;
		nx = 1;
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
	isLevelChange = level-l;
	levelChange_start = GetTickCount64();
	level = l;
}
void CMario::MarioByAttacked() {
	if (!isUntouchable)
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

		if (holdKoopa->GetState() == KOOPA_STATE_WALKING|| holdKoopa->GetState()== KOOPA_STATE_DIE_SHELL_OVERTURNED)
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
		tail->calculateSpeed(dt, x - TAIL_DISTANCE_X_WITH_MARIO * nx, y + TAIL_DISTANCE_Y_WITH_MARIO);
	if (isAttack) {
		float tail_x, tail_y;
		tail_y = y + TAIL_DISTANCE_Y_WITH_MARIO;
		tail_x = x;
		if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME)
		{
			tail->SetState(TAIL_STATE_INEFFICIENT);
			attack_start = 0;
			isAttack = false;
			return;
		}
		else if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME * 3 / 4)
		{
			tail->SetState(TAIL_STATE_ATTACK_FRONT);
			tail_x = x - TAIL_DISTANCE_X_WITH_MARIO * nx;
		}
		else if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME * 2 / 4)
		{
			tail->SetState(TAIL_STATE_IDLE_BACK);
			tail_x = x;
		}
		else if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME * 1 / 4)
		{
			tail->SetState(TAIL_STATE_ATTACK_BACK);
			tail_x = x - TAIL_DISTANCE_X_WITH_MARIO * (-nx);
		}
		tail->calculateSpeed(dt, tail_x, tail_y);
	}
}
void CMario::tailAttack() {
	if (isAttack||isSitting||ishold)return;
	if (level== MARIO_LEVEL_RACCOON) {
		isAttack = true;
		attack_start = GetTickCount64();
		tail->SetState(TAIL_STATE_IDLE_FRONT);
	}
}
void CMario::calculatePowerMeter()
{
	if (!isfly) {
		if (vx * ax > 0) {
			if (abs(vx) > MARIO_WALKING_SPEED && isOnPlatform) {
				if (GetTickCount64() - powerMeter_start > POWER_METER_TIME)
				{
					powerMeter_start = GetTickCount64();
					if (PowerMeter < 7)PowerMeter++;
				}
			}
			else
			{
				if (GetTickCount64() - powerMeter_start > POWER_METER_TIME * 2)
				{
					powerMeter_start = GetTickCount64();
					if (PowerMeter > 0) PowerMeter--;
				}
			}
		}
		else
		{
			if (GetTickCount64() - powerMeter_start > POWER_METER_TIME * 2)
			{
				powerMeter_start = GetTickCount64();
				if (PowerMeter > 0)PowerMeter--;
			}
		}
	}
}
