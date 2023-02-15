#include "ObjectWorldMap.h"
#include "Game.h"
#include "Textures.h"
#include "Animation.h"
#include "Animations.h"

CObjectWorldMap::CObjectWorldMap(float x, float y, int type)
{
	this->type = type;
	this->x = x; 
	this->y = y;
}

void CObjectWorldMap::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CObjectWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId ;
	if (type == OBJECT_WORLD_KOOPA)
		aniId = ID_ANI_WORLD_KOOPA;
	else if(type == OBJECT_WORLD_HELP)
		aniId = ID_ANI_HELP;
	else 
		aniId = ID_ANI_CACTUS;
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