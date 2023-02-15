#pragma once

#include "GameObject.h"
#define BBOX_OBJECT_WORLD 16
#define ID_ANI_CACTUS 5004
#define ID_ANI_HELP 5005
#define ID_ANI_WORLD_KOOPA 5006

#define OBJECT_WORLD_CACTUS 1
#define OBJECT_WORLD_HELP 2
#define OBJECT_WORLD_KOOPA 3
class CObjectWorldMap : public CGameObject
{
	int type;
public:
	CObjectWorldMap(float x, float y, int type);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox();
	
	int IsBlocking() { return 0; }
};