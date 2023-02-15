#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "CDoor.h"
#include "debug.h"

#define MARIO_WORLD_SPEED 0.1f
#define MARIO_WORLD_BBOX 15.7f
#define MARIO_WORLD_BBOX_WIDTH_ADJUST (16-MARIO_WORLD_BBOX)/2
#define MARIO_WORLD_BBOX_HEIGHT_ADJUST (24-MARIO_WORLD_BBOX)/2
#define MARIO_WORLD_DISTANCE_CAN_GO 32
#define MARIO_WORLD_STATE_GO_UP 100
#define MARIO_WORLD_STATE_GO_DOWN 200
#define MARIO_WORLD_STATE_GO_LEFT 300
#define MARIO_WORLD_STATE_GO_RIGHT 400
#define MARIO_WORLD_STATE_IDLE 500
#define ID_ANI_MARIO_WORLD_SMALL 5001
#define ID_ANI_MARIO_WORLD_BIG 5002
#define ID_ANI_MARIO_WORLD_RACCOON 5003

class MarioWorldMap : public CGameObject
{
	int level;
	float x_start, y_start;
	CDoor* door;

public:
	MarioWorldMap(float x, float y) : CGameObject(x, y)
	{
		door = new CDoor(0,0,0,0,0,1,0);
		SetState(MARIO_WORLD_STATE_IDLE);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return 1;
	}

	int IsBlocking() { return 1; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void StartPlayScene();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetLevel() { return level; }
};

