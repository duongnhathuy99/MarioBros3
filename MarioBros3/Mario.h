#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Koopa.h"
#include "Tail.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.12f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_WALKING_SPEED_MIN		0.01f
#define MARIO_END_SCENE_SPEED		0.06f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.0001f
#define MARIO_SLOW_ACCEL_WALK_X	0.00016f

#define MARIO_JUMP_SPEED_Y		0.4f
#define MARIO_JUMP_RUN_SPEED_Y	0.5f
#define MARIO_FLY_SPEED_Y		0.4f

#define MARIO_SLOW_FALL_SPEED_Y		0.04f
#define MARIO_FALL_SPEED_MAX	0.24f
#define MARIO_GO_IN_PIPE_SPEED_Y	0.02f

#define MARIO_GRAVITY			0.001f

#define MARIO_JUMP_DEFLECT_SPEED  0.3f

#pragma region MARIO_STATE
#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	101

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	401

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HOLD			700
#define MARIO_STATE_HOLD_RELEASE	701

#define MARIO_STATE_SLOW_FALL		800
#define MARIO_STATE_FLY				900

#define MARIO_STATE_GO_IN_PIPE		500

#define MARIO_STATE_END_SCENE		200
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

#define ID_ANI_MARIO_WALKING_FAST_RIGHT 240
#define ID_ANI_MARIO_WALKING_FAST_LEFT 241

#define ID_ANI_MARIO_FALL_RUN_RIGHT 250
#define ID_ANI_MARIO_FALL_RUN_LEFT 251

#define ID_ANI_MARIO_SMALL_TO_BIG_RIGHT 260
#define ID_ANI_MARIO_SMALL_TO_BIG_LEFT 261

#define ID_ANI_MARIO_EFFECT_SMOKE 270

#define ID_ANI_MARIO_TOPPLE 280
#define ID_ANI_MARIO_LOOK_UP 281

#define ID_ANI_MARIO_FALL_SLOW_RIGHT 290
#define ID_ANI_MARIO_FALL_SLOW_LEFT 291

#define DISTANCE_ID_ANI_MARIO 1000
#define ID_ANI_MARIO_DIE 999

#pragma endregion

#define POSITION_GO_DOWN_PIPE_X		2112.0f
#define POSITION_GO_DOWN_PIPE_Y		474.0f
#define POSITION_GO_UP_PIPE_X		2334.0f
#define POSITION_GO_UP_PIPE_Y		394.0f

#define POWER_METER_MAX 7
#define LIMITED_POSITION_Y 448
#define POSITION_CAM_Y 368
#define TILE_BBOX 16

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FIRE		3
#define	MARIO_LEVEL_RACCOON		4

#pragma region BOUNDING BOX
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16
#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12
#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)
#define MARIO_RACCOON_WIDTH_ADJUST 4
#pragma endregion

#pragma region TIME

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIME 150
#define MARIO_TAIL_ATTACK_TIME 360
#define MARIO_TAIL_SLOW_FALL_TIME 300
#define POWER_METER_TIME 200
#define MARIO_FLY_TIME 6000
#define PSWITCHES_TIME 6000
#define MARIO_LEVEL_CHANGE_TIME	600
#define MARIO_TOPPLE_TIME 500
#define MARIO_LOOK_UP_TIME 1600
#define MARIO_DIE_TIME 2000

#pragma endregion

class CMario : public CGameObject
{
	BOOLEAN isSitting, isGoInPipe, isIntro;
	BOOLEAN isKick, ishold, isAttack, isfly, isPSwitches, isUntouchable, isSlowFall, isTopple, CamYMario;
	int isLevelChange;
	float maxVx, maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float startY_GoInpipe;
	CKoopa* holdKoopa;
	CTail* tail;
	int level; 
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG attack_start;
	ULONGLONG slowFall_start;
	ULONGLONG powerMeter_start;
	ULONGLONG fly_start;
	ULONGLONG PSwitches_start;
	ULONGLONG levelChange_start;
	ULONGLONG Playing_time_start;
	ULONGLONG Topple_time_start;
	ULONGLONG Die_time_start;
	BOOLEAN isOnPlatform;
	int isCollisionWithPipe;
	int isInHiddenMap;
	int PowerMeter;

	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithPSwitches(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithItemsMenu(LPCOLLISIONEVENT e);
	int GetAniId();
	void HandleTimeMario();
public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isIntro = false;
		isGoInPipe = false;
		isOnPlatform = false;
		isInHiddenMap = 0;
		isSitting = false;
		isKick = false;
		isAttack = false;
		ishold = false;
		isfly = false;
		isSlowFall = false;
		isPSwitches = false;
		CamYMario = false;
		isUntouchable = false;
		isTopple = false;
		isLevelChange = 0;
		maxVx = 0.0f;
		maxVy = MARIO_FALL_SPEED_MAX;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		startY_GoInpipe = 0;
		isCollisionWithPipe = 0;
		level = MARIO_LEVEL_BIG;
		kick_start = -1;
		attack_start = -1;
		untouchable_start = -1;
		slowFall_start = 0;
		powerMeter_start = GetTickCount64();
		fly_start = -1;
		PSwitches_start = -1;
		levelChange_start = -1;
		Playing_time_start = GetTickCount64();
		Topple_time_start = -1;
		Die_time_start = -1;
		PowerMeter = 0;
		tail = NULL;
		holdKoopa = NULL;
		if (y < POSITION_CAM_Y)CamYMario = true;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && !isUntouchable &&!isIntro); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void MarioByAttacked();
	void SetLevel(int l);
	void StartUntouchable() { isUntouchable = true; untouchable_start = GetTickCount64(); }
	void StartKick() { isKick = true; kick_start = GetTickCount64(); }
	void releaseHoldKoopa();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	BOOLEAN IsInHiddenMap() { return isInHiddenMap; }
	void InHiddenMap() { isInHiddenMap = true; SetPosition(2200,500); }
	BOOLEAN IsPressPSwitches() { return isPSwitches; }
	BOOLEAN IsLevelChange() { return isLevelChange; }
	BOOLEAN IsFlying() { return isfly; }
	BOOLEAN IsAbleFly() {
		if (level == MARIO_LEVEL_RACCOON) return PowerMeter == POWER_METER_MAX; else return false; }
	BOOLEAN IsAbleGoDown() {
		return isCollisionWithPipe == -1;
	}
	BOOLEAN IsAbleGoUp() {
		return isCollisionWithPipe == 1;
	}
	BOOLEAN IsCamYMario() {
		return CamYMario;
	}
	void handleTail(DWORD dt);
	void handleHoldKoopa();
	void tailAttack();
	void calculatePowerMeter();
	void setLuigi() {
		isIntro = true;
		 level = MARIO_LEVEL_FIRE;
	}
	void setDirectionMario(int direct) {
		isIntro = true;
		nx = direct;
	}
	void setAccel() { ax = 0; }
	int GetLevel() { return level; }
	int GetPowerMeter() { return PowerMeter; }

};