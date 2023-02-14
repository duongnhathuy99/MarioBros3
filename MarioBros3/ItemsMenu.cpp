#include "ItemsMenu.h"
#include "Debug.h"

ItemsMenu::ItemsMenu(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	typeItems = 1;
	itemsMenu_start = 0;
	state = ITEMS_MENU_STATE_IDLE;
	//SetState(LEAF_STATE_FLY_UP);
}

void ItemsMenu::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ITEMS_MENU_BBOX_WIDTH / 2;
	top = y - ITEMS_MENU_HEIGHT / 2;
	right = left + ITEMS_MENU_BBOX_WIDTH;
	bottom = top + ITEMS_MENU_HEIGHT;
}

void ItemsMenu::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void ItemsMenu::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

}

void ItemsMenu::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (state == ITEMS_MENU_STATE_FLY_UP_SPINNING && y < ITEMS_MENU_POSSITION_Y_DELETE) Delete();
	//time items menu change
	if (GetTickCount64() - itemsMenu_start > ITEMS_MENU_TIME && state == ITEMS_MENU_STATE_IDLE)
	{
		itemsMenu_start = GetTickCount64();
		typeItems++;
		if (typeItems > ITEMS_MENU_FIRE_FLOWER ) typeItems = ITEMS_MENU_MUSHROOM;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void ItemsMenu::Render()
{
	int aniId ;
	
	if (typeItems == ITEMS_MENU_MUSHROOM)
		aniId = ID_ANI_MUSHROOM;
	else if (typeItems == ITEMS_MENU_STAR)
		aniId = ID_ANI_STAR;
	else 
		aniId = ID_ANI_FIRE_FLOWER;
	if (state == ITEMS_MENU_STATE_FLY_UP_SPINNING) aniId += 3;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void ItemsMenu::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEMS_MENU_STATE_IDLE:
		
		break;
	case ITEMS_MENU_STATE_FLY_UP_SPINNING:
	
		vy = -ITEMS_MENU_SPEED_Y;
		break;
	}
}
