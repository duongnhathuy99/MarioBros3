#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Koopa.h"
#include "Tail.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_RUN_SPEED_Y	0.7f

#define MARIO_SLOW_FALL_SPEED_Y		0.05f
#define MARIO_FALL_SPEED_MAX	0.24f

#define MARIO_GRAVITY			0.0018f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#pragma region MARIO_STATE
#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HOLD			700
#define MARIO_STATE_HOLD_RELEASE	701

#define MARIO_STATE_SLOW_FALL		800
#pragma endregion

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 100
#define ID_ANI_MARIO_IDLE_LEFT 101

#define ID_ANI_MARIO_WALKING_RIGHT 110
#define ID_ANI_MARIO_WALKING_LEFT 111

#define ID_ANI_MARIO_RUNNING_RIGHT 120
#define ID_ANI_MARIO_RUNNING_LEFT 121

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 130
#define ID_ANI_MARIO_JUMP_WALK_LEFT 131

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 140
#define ID_ANI_MARIO_JUMP_RUN_LEFT 141

#define ID_ANI_MARIO_SIT_RIGHT 150
#define ID_ANI_MARIO_SIT_LEFT 151

#define ID_ANI_MARIO_SKID_RIGHT 160
#define ID_ANI_MARIO_SKID_LEFT 161

#define ID_ANI_MARIO_KICK_RIGHT 170
#define ID_ANI_MARIO_KICK_LEFT 171

#define ID_ANI_MARIO_HOLD_ILDE_RIGHT 180
#define ID_ANI_MARIO_HOLD_ILDE_LEFT 181

#define ID_ANI_MARIO_HOLD_WALK_RIGHT 190
#define ID_ANI_MARIO_HOLD_WALK_LEFT 191

#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 200
#define ID_ANI_MARIO_HOLD_JUMP_LEFT 201

#define ID_ANI_MARIO_ATTACK_RIGHT 210
#define ID_ANI_MARIO_ATTACK_LEFT 211

#define ID_ANI_MARIO_TAIL_BACK 220
#define ID_ANI_MARIO_TAIL_FRONT 221

#define ID_ANI_MARIO_FALL_WALK_RIGHT 230
#define ID_ANI_MARIO_FALL_WALK_LEFT 231

#define DISTANCE_ID_ANI_MARIO 1000
#define ID_ANI_MARIO_DIE 999

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FIRE		3
#define	MARIO_LEVEL_RACCOON		4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16
#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)
#define MARIO_RACCOON_WIDTH_ADJUST 4

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIME 150
#define MARIO_TAIL_ATTACK_TIME 360
#define MARIO_TAIL_SLOW_FALL_TIME 250

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isKick, ishold, isAttack;
	float maxVx, maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	CKoopa* holdKoopa;
	CTail* tail;
	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG attack_start;
	ULONGLONG slowFall_start;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);

	int GetAniId();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isKick = false;
		isAttack = false;
		ishold = false;
		maxVx = 0.0f;
		maxVy = MARIO_FALL_SPEED_MAX;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		kick_start = -1;
		attack_start = -1;
		untouchable_start = -1;
		slowFall_start = -1;
		isOnPlatform = false;
		coin = 0;
		tail = NULL;
		holdKoopa = NULL;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void MarioByAttacked();
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKick() { isKick = true; kick_start = GetTickCount64(); }
	void releaseHoldKoopa();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	void handleTail(DWORD dt);
	void handleHoldKoopa();
	void tailAttack();
};