#pragma once
#include "GameObject.h"
#define ITEMS_MENU_SPEED_Y 0.05f

#define ITEMS_MENU_BBOX_WIDTH 16
#define ITEMS_MENU_HEIGHT 14

#define ITEMS_MENU_MUSHROOM 1
#define ITEMS_MENU_STAR 2
#define ITEMS_MENU_FIRE_FLOWER 3

#define ITEMS_MENU_STATE_IDLE 1
#define ITEMS_MENU_STATE_FLY_UP_SPINNING 2

#define ID_ANI_STAR 7008
#define ID_ANI_FIRE_FLOWER 7009
#define ID_ANI_MUSHROOM 7010

#define ID_ANI_SPINNING_STAR 7011
#define ID_ANI_SPINNING_FIRE_FLOWER 7012
#define ID_ANI_SPINNING_MUSHROOM 7013

#define ITEMS_MENU_POSSITION_Y_DELETE 256
#define ITEMS_MENU_TIME 300

class ItemsMenu : public CGameObject
{
protected:
	float ax;
	float ay;
	int typeItems;
	ULONGLONG itemsMenu_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	ItemsMenu(float x, float y);
	virtual void SetState(int state);
	int GetTypeItems() { return typeItems; }
};