#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Coin.h"

#define ID_ANI_BRICK_ITEM 6000
#define ID_ANI_BRICK_UNBOX 6001
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15

#define QUESTION_BRICK_STATE_ITEM 1
#define QUESTION_BRICK_STATE_MOVEUP 2
#define QUESTION_BRICK_STATE_MOVEDOWN 3
#define QUESTION_BRICK_STATE_UNBOX 4

#define SPEED_QUESTION_BRICK 0.04f
#define DISTANCE_QUESTION_BRICK_MOVEUP 7

class CQuestionBrick : public CGameObject{
	bool questionBrick_unbox;
	float startY;
	CCoin* coin;
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {
		state = QUESTION_BRICK_STATE_ITEM;
		questionBrick_unbox = false;
		startY = y;
		coin = NULL;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};

