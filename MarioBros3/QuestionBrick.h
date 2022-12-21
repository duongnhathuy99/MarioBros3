#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PlayScene.h"

#define ID_ANI_BRICK_ITEM 9000
#define ID_ANI_BRICK_UNBOX 9001
#define BRICK_BBOX 16
//#define BRICK_BBOX_WIDTH 15
//#define BRICK_BBOX_HEIGHT 15

#define QUESTION_BRICK_STATE_ITEM 1
#define QUESTION_BRICK_STATE_MOVEUP 2
#define QUESTION_BRICK_STATE_MOVEDOWN 3
#define QUESTION_BRICK_STATE_UNBOX 4

#define SPEED_QUESTION_BRICK 0.04f
#define DISTANCE_QUESTION_BRICK_MOVEUP 7

#define ITEM_COIN 1
#define ITEM_MUSHROOM 2
#define ITEM_LEAF 3

class CQuestionBrick : public CGameObject{
	bool questionBrick_unbox;
	float startY;
	int item;
public:
	CQuestionBrick(float x, float y,int Item) : CGameObject(x, y) {
		state = QUESTION_BRICK_STATE_ITEM;
		questionBrick_unbox = false;
		startY = y;
		item = Item;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};

