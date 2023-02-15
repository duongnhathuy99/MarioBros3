#include "WorldSceneKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "MarioWorldMap.h"
#include "CWorldScene.h"

void CWorldSceneKeyEventHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	MarioWorldMap* marioWorld = (MarioWorldMap*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		
		break;
	
	}
}

void CWorldSceneKeyEventHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	
}

void CWorldSceneKeyEventHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	MarioWorldMap* marioWorld = (MarioWorldMap*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (marioWorld->GetState() != MARIO_WORLD_STATE_IDLE) return;
	if (game->IsKeyDown(DIK_UP))
	{
		marioWorld->SetState(MARIO_WORLD_STATE_GO_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		marioWorld->SetState(MARIO_WORLD_STATE_GO_DOWN);
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		marioWorld->SetState(MARIO_WORLD_STATE_GO_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		marioWorld->SetState(MARIO_WORLD_STATE_GO_LEFT);
	}

}