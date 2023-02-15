#pragma once
#include "GameObject.h"

#define DOOR_BBOX_WIDTH 16
#define DOOR_TYPE_COIN 0
#define DOOR_TYPE_1 1
#define DOOR_TYPE_2 2
#define DOOR_TYPE_3 3
#define DOOR_TYPE_4 4
#define DOOR_TYPE_5 5
#define DOOR_TYPE_6 6
#define DOOR_TYPE_MUSHROOM 7
#define DOOR_TYPE_BOSS_CASTLE 8
#define DOOR_TYPE_PRINCESS_CASTLE 9
#define DOOR_TYPE_SPADES 10

class CDoor : public CGameObject
{
protected:
	BOOLEAN top_Direction, bot_Direction, left_Direction, right_Direction;
	int type;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CDoor(float x, float y, int t, BOOLEAN left, BOOLEAN top,  BOOLEAN right, BOOLEAN bot):CGameObject(x, y)
	{
		type = t;
		top_Direction = top;
		bot_Direction = bot; 
		left_Direction = left; 
		right_Direction = right;
	}
	int GetType() { return type; }
	int GetTop() { return top_Direction; }
	int GetBot() { return bot_Direction; }
	int GetRight() { return right_Direction; }
	int GetLeft() { return left_Direction; }
	virtual void SetState(int state);
};

