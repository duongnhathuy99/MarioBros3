#pragma once
#include "GameObject.h"

class CPipe : public CGameObject
{
protected:
	int height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteId_top_left, spriteId_top_right, spriteId_bot_left, spriteId_bot_right;
public:
	CPipe(float x, float y,
		float cell_width, float cell_height, int height, int spriteId_top_left, int spriteId_top_right, int spriteId_bot_left, int spriteId_bot_right) :CGameObject(x, y)
	{
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteId_top_left = spriteId_top_left;
		this->spriteId_top_right = spriteId_top_right;
		this->spriteId_bot_left = spriteId_bot_left;
		this->spriteId_bot_right = spriteId_bot_right;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; };
};

