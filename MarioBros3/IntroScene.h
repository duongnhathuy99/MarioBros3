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

#define MILESTONE_1 1
#define MILESTONE_2 2
#define MILESTONE_3 3
#define MILESTONE_4 4
#define MILESTONE_5 5
#define MILESTONE_6 6
#define MILESTONE_7 7

#define TIME_MILESTONE_1 1000
#define TIME_MILESTONE_2 2200
#define TIME_MILESTONE_3 3200
#define TIME_MILESTONE_4 3700
#define TIME_MILESTONE_5 7000
#define TIME_MILESTONE_6 9000
#define TIME_MILESTONE_7 7000


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
	CMushroom* mushroom = new CMushroom(48,0);
	CGoomba* goomba = new CGoomba(75, 0,0);
	CLeaf* leaf = new CLeaf(112, 0);
	CKoopa* koopa = new CKoopa(120, 0, 0);

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
			mario->setMario();
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
			milestone++;
		}
	}
	LPGAMEOBJECT GetPlayer() { return player; }

	void AddHeadObject(CGameObject* obj) { objects.insert(objects.begin() , obj); }
	void AddTailObject(CGameObject* obj) { objects.insert(objects.end() , obj); }
	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;
