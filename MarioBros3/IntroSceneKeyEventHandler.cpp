#include "IntroSceneKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "AssetIDs.h"
#include "IntroScene.h"

void CIntroSceneKeyEventHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	//MarioWorldMap* marioWorld = (MarioWorldMap*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_W:
		CGame::GetInstance()->InitiateSwitchScene(ID_WORLD_SCENE);
		break;
	}
}

void CIntroSceneKeyEventHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}

void CIntroSceneKeyEventHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();

	/*if (game->IsKeyDown(DIK_UP))
	{
		
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		
	}*/

}