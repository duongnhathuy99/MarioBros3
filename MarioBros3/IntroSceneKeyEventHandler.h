#pragma once
#include "Scene.h"

class CIntroSceneKeyEventHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroSceneKeyEventHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};

