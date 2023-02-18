#include "HUD.h"
#include "ItemsMenu.h"
#include "Sprite.h"
#include "Sprites.h"
#include "AssetIDs.h"

HUD* HUD::__instance = NULL;

void HUD::Render() {
	float cx, cy;
	CGame* game = CGame::GetInstance();
	game->GetCamPos(cx, cy);
	cx += game->GetBackBufferWidth() / 2;
	cy += game->GetBackBufferHeight() - DISTANCE_HUD_HEIGHT;
	CSprites* s = CSprites::GetInstance();

	s->Get(ID_SPRITE_HUD_BACKGROUND)->Draw(cx, cy);
	s->Get(ID_SPRITE_HUD_BOARD)->Draw(cx, cy);
	

	if (dynamic_cast<CMario*>(((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer()))
	{
		time = TIME_START_PLAYSCENE - INT((GetTickCount64() - Playing_time_start) / MILI_1000_SECOND);
		//POWER METERs
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		float mario_x, mario_y;
		mario->GetPosition(mario_x, mario_y);
		DrawPowerMeter(mario->GetPowerMeter(), cx - 60, cy - 3);
		if (mario->GetState() == MARIO_STATE_END_SCENE && mario_x > MAP_HORIZONTAL_LIMIT) {
			s->Get(ID_SPRITE_END_SCENE)->Draw(cx, cy - 170);
			int item;
			if (item3) item = item3;
			else if (item2) item = item2;
			else item = item1;
			DrawItem(item, cx + 62, cy - 162);
			if (time > 0) {
				Playing_time_start -= MILI_1000_SECOND;
				point += POINT_50;
			}
			else
				game->InitiateSwitchScene(ID_WORLD_SCENE);
		}
	}
	//COIN
	DrawNumber(coin / 10, cx + 20, cy - 3);
	DrawNumber(coin % 10, cx + 28, cy - 3);
	//TIME
	DrawNumber(time % 10, cx + 28, cy + 5);
	DrawNumber(time / 10 % 10, cx + 20, cy + 5);
	DrawNumber(time / 100, cx + 12, cy + 5);
	//POINT
	DrawNumber(point % 10, cx - 12, cy + 5);
	DrawNumber(point /10 % 10, cx - 20, cy + 5);
	DrawNumber(point /100 % 10, cx - 28, cy + 5);
	DrawNumber(point /1000 % 10, cx - 36, cy + 5);
	DrawNumber(point /10000 % 10, cx - 44, cy + 5);
	DrawNumber(point /100000 % 10, cx - 52, cy + 5);
	DrawNumber(point /1000000, cx - 60, cy + 5);
	//HEALTH
	DrawNumber(health / 10, cx - 84, cy + 5);
	DrawNumber(health % 10, cx - 76, cy + 5);
	//ITEMS MENU
	DrawItem(item1, cx + 56, cy );
	DrawItem(item2, cx + 80, cy );
	DrawItem(item3, cx + 104, cy );
}
void HUD::DrawNumber(int number, float x, float y) {
	CSprites* s = CSprites::GetInstance();
	switch (number)
	{
	case 0:
		s->Get(ID_SPRITE_NUMBER_0)->Draw(x, y);
		break;
	case 1:
		s->Get(ID_SPRITE_NUMBER_1)->Draw(x, y);
		break;
	case 2:
		s->Get(ID_SPRITE_NUMBER_2)->Draw(x, y);
		break;
	case 3:
		s->Get(ID_SPRITE_NUMBER_3)->Draw(x, y);
		break;
	case 4:
		s->Get(ID_SPRITE_NUMBER_4)->Draw(x, y);
		break;
	case 5:
		s->Get(ID_SPRITE_NUMBER_5)->Draw(x, y);
		break;
	case 6:
		s->Get(ID_SPRITE_NUMBER_6)->Draw(x, y);
		break;
	case 7:
		s->Get(ID_SPRITE_NUMBER_7)->Draw(x, y);
		break;
	case 8:
		s->Get(ID_SPRITE_NUMBER_8)->Draw(x, y);
		break;
	case 9:
		s->Get(ID_SPRITE_NUMBER_9)->Draw(x, y);
		break;
	default:
		break;
	}
}
void HUD::DrawPowerMeter(int power, float x, float y) {
	CSprites* s = CSprites::GetInstance();
	for (int i = 0; i < power; i++)
	{
		if (i == 6) {
			s->Get(ID_SPRITE_POWER_P)->Draw(x + i*8+5, y );
			break;
		}
		s->Get(ID_SPRITE_POWER)->Draw(x + 8 * i , y );
	}
}
void HUD::DrawItem(int item,float x, float y) {
	CSprites* s = CSprites::GetInstance();
	switch (item)
	{
	case ITEMS_MENU_MUSHROOM:
		s->Get(ID_SPRITE_MUSHROOM)->Draw(x, y);
		break;
	case ITEMS_MENU_FIRE_FLOWER:
		s->Get(ID_SPRITE_FIRE_FLOWER)->Draw(x, y);
		break;
	case ITEMS_MENU_STAR:
		s->Get(ID_SPRITE_STAR)->Draw(x, y);
		break;
	default:
		break;
	}
}