#pragma once
#include "GameObject.h"

class CSemisolidPlatform : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
public:
	CSemisolidPlatform(float x, float y,
		float cell_width, float cell_height, int length) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 0; t = 1; b = 0; r = 0; }
	int IsBlocking() { return 1; }
};

