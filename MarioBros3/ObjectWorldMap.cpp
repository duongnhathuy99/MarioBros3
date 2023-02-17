#include "ObjectWorldMap.h"
#include "Game.h"
#include "Textures.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"

CObjectWorldMap::CObjectWorldMap(float x, float y, float vx, float vy, int type)
{
	this->type = type;
	this->x = x; 
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	x_start = x;
}

void CObjectWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == OBJECT_WORLD_KOOPA && abs(x_start - x) >= RANGE_KOOPA_WALK) vx = -vx;
	if (type == OBJECT_INTRO_SUPER_MARIO_BROS3 && y > 82) { type = OBJECT_INTRO_SUPER_MARIO_BROS3_VIBRATE; vy = 0; y = 80; }
	if (type == OBJECT_INTRO_SUPER_MARIO_BROS3_VIBRATE) if (y > 80)y = 80 - 1; else y = 80 + 1;
	x += vx * dt;
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
}
void CObjectWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	CSprites* sprite = CSprites::GetInstance();

	int aniId = 0;
	int spriteId = 0;
	switch (type)
	{
	case OBJECT_WORLD_CACTUS:
		aniId = ID_ANI_CACTUS;
		break;
	case OBJECT_WORLD_HELP:
		aniId = ID_ANI_HELP;
		break;
	case OBJECT_WORLD_KOOPA:
		if (vx > 0)
			aniId = ID_ANI_WORLD_KOOPA_RIGHT;
		else
			aniId = ID_ANI_WORLD_KOOPA_LEFT;
		break;
	case OBJECT_INTRO_CURTAIN:
		spriteId = ID_SPRITE_INTRO_CURTAIN;
		break;
	case OBJECT_INTRO_SUPER_MARIO_BROS3:
		spriteId = ID_SPRITE_INTRO_SUPER_MARIO_BROS3;
		break;
	case OBJECT_INTRO_SUPER_MARIO_BROS3_VIBRATE:
		spriteId = ID_SPRITE_INTRO_SUPER_MARIO_BROS3;
		break;
	case OBJECT_INTRO_NUMER_3:
		aniId = ID_ANI_INTRO_NUMBER_3;
		break;
	case OBJECT_INTRO_TREE_LEFT:
		spriteId = ID_SPRITE_INTRO_TREE_LEFT;
		break;
	case OBJECT_INTRO_TREE_RIGHT:
		spriteId = ID_SPRITE_INTRO_TREE_RIGHT;
		break;
	case OBJECT_INTRO_CURTAIN_FOOT:
		spriteId = ID_SPRITE_INTRO_CURTAIN_FOOT;
		break;
	case OBJECT_INTRO_BACKGROUND:
		spriteId = ID_SPRITE_INTRO_BACKGROUND;
		break;
	}
	if(spriteId)
		sprite->Get(spriteId)->Draw(x, y);
	else
		animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CObjectWorldMap::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BBOX_OBJECT_WORLD /2;
	t = y - BBOX_OBJECT_WORLD /2;
	r = x + BBOX_OBJECT_WORLD /2;
	b = y + BBOX_OBJECT_WORLD /2;
}