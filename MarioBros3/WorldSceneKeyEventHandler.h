#pragma once
#include "Scene.h"

class CWorldSceneKeyEventHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorldSceneKeyEventHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
