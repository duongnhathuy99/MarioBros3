#include "HUB.h"
#include "Sprite.h"
#include "Sprites.h"
#include "PlayScene.h"
void HUB::Render() {
	float cx, cy;
	CGame* game = CGame::GetInstance();
	game->GetCamPos(cx, cy);
	cx += game->GetBackBufferWidth() / 2;
	cy += game->GetBackBufferHeight() - DISTANCE_HUB_HEIGHT;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CSprites* s = CSprites::GetInstance();

	s->Get(ID_SPRITE_HUB_BACKGROUND)->Draw(cx, cy);
	s->Get(ID_SPRITE_HUB_BOARD)->Draw(cx, cy);


	//COIN
	DrawNumber(mario->GetCoin() / 10, cx + 20, cy - 3);
	DrawNumber(mario->GetCoin() % 10, cx + 28, cy - 3);
	//TIME
	DrawNumber(mario->GetTime() % 10, cx + 28, cy + 5);
	DrawNumber(mario->GetTime() / 10 % 10, cx + 20, cy + 5);
	DrawNumber(mario->GetTime() / 100, cx + 12, cy + 5);
	//POINT
	DrawNumber(mario->GetPoint() % 10, cx - 12, cy + 5);
	DrawNumber(mario->GetPoint()/10 % 10, cx - 20, cy + 5);
	DrawNumber(mario->GetPoint()/100 % 10, cx - 28, cy + 5);
	DrawNumber(mario->GetPoint()/1000 % 10, cx - 36, cy + 5);
	DrawNumber(mario->GetPoint()/10000 % 10, cx - 44, cy + 5);
	DrawNumber(mario->GetPoint()/100000 % 10, cx - 52, cy + 5);
	DrawNumber(mario->GetPoint()/1000000, cx - 60, cy + 5);
	//HEALTH
	DrawNumber(mario->GetHealth() / 10, cx - 84, cy + 5);
	DrawNumber(mario->GetHealth() % 10, cx - 76, cy + 5);
	//POWER METERs
	DrawPowerMeter(mario->GetPowerMeter(), cx - 60, cy - 3);
}
void HUB::DrawNumber(int number, float x, float y) {
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
void HUB::DrawPowerMeter(int power, float x, float y) {
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
void HUB::DrawItem() {}