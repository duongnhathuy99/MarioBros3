#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Koopa.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

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

#define ID_ANI_MARIO_BRACE_RIGHT 160
#define ID_ANI_MARIO_BRACE_LEFT 161

#define ID_ANI_MARIO_KICK_RIGHT 170
#define ID_ANI_MARIO_KICK_LEFT 171

#define ID_ANI_MARIO_HOLD_ILDE_RIGHT 180
#define ID_ANI_MARIO_HOLD_ILDE_LEFT 181

#define ID_ANI_MARIO_HOLD_WALK_RIGHT 190
#define ID_ANI_MARIO_HOLD_WALK_LEFT 191

#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 200
#define ID_ANI_MARIO_HOLD_JUMP_LEFT 201

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1101

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1110
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1111

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1120
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1121

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1130
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1131

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1140
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1141

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1160
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1161

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1170
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1171

#define ID_ANI_MARIO_SMALL_HOLD_RIGHT 1180
#define ID_ANI_MARIO_SMALL_HOLD_LEFT 1181

#define ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 1190
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 1191

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1200
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1201
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

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIME 150

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isKick, ishold;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	CKoopa* holdKoopa;
	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;

	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isKick = false;
		ishold = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		kick_start = -1;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;

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

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKick() { isKick = true; kick_start = GetTickCount64(); }
	void releaseHoldKoopa();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void handleHoldKoopa();
};