#pragma once

#include "GameObject.h"
#define BBOX_OBJECT_WORLD 16
#define RANGE_KOOPA_WALK 16 

#define ID_ANI_CACTUS 5004
#define ID_ANI_HELP 5005
#define ID_ANI_WORLD_KOOPA_RIGHT 5006
#define ID_ANI_WORLD_KOOPA_LEFT 5007
#define ID_ANI_INTRO_NUMBER_3 5500

#define ID_SPRITE_INTRO_CURTAIN 55001
#define ID_SPRITE_INTRO_SUPER_MARIO_BROS3 55002
#define ID_SPRITE_INTRO_TREE_LEFT 55008
#define ID_SPRITE_INTRO_TREE_RIGHT 55009
#define ID_SPRITE_INTRO_1PLAYER 55010
#define ID_SPRITE_INTRO_2PLAYER 55011
#define ID_SPRITE_INTRO_CURTAIN_FOOT 55003
#define ID_SPRITE_INTRO_BACKGROUND 55015

#define OBJECT_WORLD_CACTUS 1
#define OBJECT_WORLD_HELP 2
#define OBJECT_WORLD_KOOPA 3

#define OBJECT_INTRO_CURTAIN 4
#define OBJECT_INTRO_SUPER_MARIO_BROS3 5
#define OBJECT_INTRO_SUPER_MARIO_BROS3_VIBRATE 6
#define OBJECT_INTRO_NUMER_3 7
#define OBJECT_INTRO_TREE_LEFT 8
#define OBJECT_INTRO_TREE_RIGHT 9
#define OBJECT_INTRO_CURTAIN_FOOT 10
#define OBJECT_INTRO_BACKGROUND 11
#define OBJECT_INTRO_1PLAYER 12
#define OBJECT_INTRO_2PLAYER 13

class CObjectWorldMap : public CGameObject
{
	int type;
	float x_start;
public:
	CObjectWorldMap(float x, float y, float vx, float vy, int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetType(int type) { this->type = type; }
	
	int IsBlocking() { return 0; }
};