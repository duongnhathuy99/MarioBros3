#pragma once
#include "Scene.h"
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Map.h"

#include "Mario.h"
#include "Platform.h"
#include "ObjectWorldMap.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "Koopa.h"
#include "Goomba.h"
#include "Star.h"
#include "BlackKoopa.h"

#define MILESTONE_1 1
#define MILESTONE_2 2
#define MILESTONE_3 3
#define MILESTONE_4 4
#define MILESTONE_5 5
#define MILESTONE_6 6
#define MILESTONE_7 7
#define MILESTONE_8 8
#define MILESTONE_9 9
#define MILESTONE_10 10
#define MILESTONE_11 11
#define MILESTONE_12 12
#define MILESTONE_13 13
#define MILESTONE_14 14
#define MILESTONE_15 15
#define MILESTONE_16 16
#define MILESTONE_17 17
#define MILESTONE_18 18
#define MILESTONE_19 19

#define TIME_MILESTONE_1 1000
#define TIME_MILESTONE_2 2200
#define TIME_MILESTONE_3 3200
#define TIME_MILESTONE_4 3700
#define TIME_MILESTONE_5 7000
#define TIME_MILESTONE_6 9000
#define TIME_MILESTONE_7 11500
#define TIME_MILESTONE_8 11500
#define TIME_GOOMBA_WALK 13300
#define TIME_MILESTONE_9 11500
#define TIME_MILESTONE_10 14700
#define TIME_MILESTONE_11 17500
#define TIME_MILESTONE_12 18500
#define TIME_MILESTONE_13 19000
#define TIME_MILESTONE_14 19400
#define TIME_MILESTONE_15 20400
#define TIME_MILESTONE_16 21400
#define TIME_MILESTONE_17 23400
#define TIME_MILESTONE_18 23400
#define TIME_MILESTONE_19 23400

class CIntroScene : public CScene
{
	LPGAMEOBJECT player;
	LPMAP map;
	vector<LPGAMEOBJECT> objects;
	ULONGLONG time_intro_start = GetTickCount64();
	int milestone = MILESTONE_1;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);

	void LoadAssets(LPCWSTR assetFile);
	CMario* luigi = new CMario(8, 175);
	CMario* mario = new CMario(250, 175);
	CObjectWorldMap* SPMarioBros3 = new CObjectWorldMap(128, 0, 0, 0, OBJECT_INTRO_SUPER_MARIO_BROS3);
	CObjectWorldMap* curtainFoot = new CObjectWorldMap(128, 8, 0, 0, OBJECT_INTRO_CURTAIN_FOOT);
	CObjectWorldMap* number3 = new CObjectWorldMap(141, 118, 0, 0, OBJECT_INTRO_NUMER_3);
	CObjectWorldMap* treeLeft = new CObjectWorldMap(32, 140, 0, 0, OBJECT_INTRO_TREE_LEFT);
	CObjectWorldMap* treeRight = new CObjectWorldMap(224, 140, 0, 0, OBJECT_INTRO_TREE_RIGHT);
	CObjectWorldMap* bg_intro = new CObjectWorldMap(128, 120, 0, 0, OBJECT_INTRO_BACKGROUND);
	CMushroom* mushroom = new CMushroom(48,0,TYPE_MUSHROOM);
	CGoomba* goomba = new CGoomba(75, 0,0);
	CLeaf* leaf = new CLeaf(112, 0);
	CKoopa* koopa = new CKoopa(120, 0, 0);
	CBlackKoopa* Black_koopa = new CBlackKoopa(200, 0);
	CStar* star = new CStar(220, 0);

public:
	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void scriptIntro()
	{
		ULONGLONG time_now = GetTickCount64() - time_intro_start;
		if (time_now > TIME_MILESTONE_1 && milestone == MILESTONE_1)
		{
			
			luigi->setLuigi();
			mario->setDirectionMario(-1);
			AddHeadObject(mario);
			AddHeadObject(luigi);

			milestone++;
		}
		else if (time_now > TIME_MILESTONE_2 && milestone == MILESTONE_2)
		{

			mario->SetSpeed(-0.00001f, 0);
			luigi->SetSpeed(0.00001f, 0);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_3 && milestone == MILESTONE_3)
		{

			mario->SetSpeed(-0.08f, 0);
			luigi->SetSpeed(0.08f, 0);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_4 && milestone == MILESTONE_4)
		{
			luigi->SetSpeed(0.08f, -0.5f);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_5 && milestone == MILESTONE_5)
		{
			mario->SetState(MARIO_STATE_SIT_RELEASE);
			SPMarioBros3->SetSpeed(0, 0.07f);
			AddHeadObject(SPMarioBros3);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_6 && milestone == MILESTONE_6)
		{
			SPMarioBros3->SetType(OBJECT_INTRO_SUPER_MARIO_BROS3);
			AddHeadObject(curtainFoot);
			AddTailObject(number3);
			AddHeadObject(treeLeft);
			AddHeadObject(treeRight);
			AddHeadObject(bg_intro);
			AddTailObject(mushroom);
			AddTailObject(leaf);
			goomba->SetSpeed(0,0);
			AddTailObject(goomba);
			koopa->SetState(KOOPA_STATE_SHELL);
			AddTailObject(koopa);
			AddTailObject(Black_koopa);
			AddTailObject(star);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_7 && milestone == MILESTONE_7)
		{
			mario->SetSpeed(0,-0.45f);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_8 && milestone == MILESTONE_8)
		{
			if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
			{
				mario->SetSpeed(-0.05f,0);
				mario->SetState(MARIO_STATE_SLOW_FALL);
				milestone++;
			}
		}
		else if (time_now > TIME_MILESTONE_9 && milestone == MILESTONE_9)
		{
			if (time_now > TIME_GOOMBA_WALK && goomba->GetState() == GOOMBA_STATE_WALKING)
				goomba->SetSpeed(-GOOMBA_WALKING_SPEED,0);
			if (goomba->GetState() == GOOMBA_STATE_DIE)
			{
				milestone++;
			}
			else
				mario->SetState(MARIO_STATE_SLOW_FALL);
		}
		else if (time_now > TIME_MILESTONE_10 && milestone == MILESTONE_10)
		{
			mario->SetSpeed(0.06f, 0);
			mario->setDirectionMario(1);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_11 && milestone == MILESTONE_11)
		{
			mario->SetSpeed(0, 0);
			koopa->SetState(KOOPA_STATE_SHELL);
			koopa->SetPosition(250, 175);
			luigi->SetPosition(300, 175);
			luigi->SetState(MARIO_STATE_RUNNING_LEFT);
			luigi->SetSpeed(-0.08f, 0);
			luigi->setAccel();
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_12 && milestone == MILESTONE_12)
		{
			mario->SetSpeed(-0.08f, 0);
			luigi->SetSpeed(0, 0);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_13 && milestone == MILESTONE_13)
		{
			luigi->releaseHoldKoopa();
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_14 && milestone == MILESTONE_14)
		{
			mario->setDirectionMario(-1);
			mario->SetSpeed(-0.08f, -0.3f);
		milestone++;
		}
		else if (time_now > TIME_MILESTONE_15 && milestone == MILESTONE_15)
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			mario->SetSpeed(0.08f, 0);
			mario->setAccel();
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_16 && milestone == MILESTONE_16)
		{
			mario->releaseHoldKoopa();
			mario->SetSpeed(0, 0); 
			luigi->SetSpeed(0.08f, 0);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_17 && milestone == MILESTONE_17)
		{
			koopa->SetPosition(0, 175);
			milestone++;
		}
		else if (time_now > TIME_MILESTONE_18 && milestone == MILESTONE_18)
		{
			if (mario->GetLevel() == MARIO_LEVEL_BIG)
			{
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->SetSpeed(0.08f, 0);
				AddTailObject(treeRight);
				milestone++;
			}
		}
	}
	LPGAMEOBJECT GetPlayer() { return player; }

	void AddHeadObject(CGameObject* obj) { objects.insert(objects.begin() , obj); }
	void AddTailObject(CGameObject* obj) { objects.insert(objects.end()-1 , obj); }
	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;
