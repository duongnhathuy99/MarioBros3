#include "Map.h"
#include"debug.h"
Map::Map(int ID, LPCWSTR FilePath_data, int Map_rows, int  Map_cols, int Tile_rows, int Tile_cols, int Tile_width, int Tile_height)
{
	this->Id = ID;

	this->MapFilePath = FilePath_data;


	// rows of Map
	this->Map_Rows = Map_rows;
	// cols of Map
	this->Map_Cols = Map_cols;

	// rows of tilemap
	this->Tile_Rows = Tile_rows;
	// cols of tilemap
	this->Tile_Cols = Tile_cols;

	this->Tile_Width = Tile_width;
	this->Tile_Height = Tile_height;

	LoadMapSprite();
	LoadFileMap();
}
void Map::LoadFileMap()
{
	// Load info map form file
	ifstream f;
	f.open(MapFilePath);
	if (f.fail())
	{
		f.close();
		return;
	}
	for (int i = 0; i < Map_Rows; i++)
	{
		for (int j = 0; j < Map_Cols; j++)
		{
			f >> tilemap[i][j];
		}
	}
	f.close();
}

void Map::LoadMapSprite()
{
	// Load sprite for map

	CTextures* texture = CTextures::GetInstance();
	LPTEXTURE texMap = texture->Get(Id);
	int id_sprite = Id + 1;
	for (int i = 0; i < Tile_Rows; i++)
	{
		for (int j = 0; j < Tile_Cols; j++)
		{
			//DebugOut(L"id_sprite:%d   \n", id_sprite);
			CSprites::GetInstance()->Add(id_sprite, Tile_Width * j, Tile_Height * i, Tile_Width * (j + 1) - 1, Tile_Height * (i + 1) - 1, texMap);
			id_sprite ++;
		}
	}
}

void Map::Draw()
{
	CSprites* sprites = CSprites::GetInstance();
	CGame* cgame = CGame::GetInstance();
	float x, y;
	int firstcol, lastcol, firstrow, lastrow;
	cgame->GetCamPos(x, y);
	firstcol = (int)x / Tile_Width;
	if (firstcol < 0) { firstcol = 0; }
	lastcol = ((int)x + cgame->GetBackBufferWidth()) / Tile_Width + 1;
	firstrow = (int)y / Tile_Width;
	if (firstrow < 0) { firstrow = 0; }
	lastrow = ((int)y + cgame->GetBackBufferHeight()) / Tile_Width + 1;
	//DebugOut(L"fcol:%d   lcol:%d\n", firstrow, lastrow);
	for (int i = firstrow; i <= lastrow; i++)
	{
		for (int j = firstcol; j <= lastcol; j++)
		{
			if (tilemap[i][j])
				sprites->Get(tilemap[i][j] + Id)->Draw((float)Tile_Width * j, (float)Tile_Height * i);
		}
	}
}


Map::~Map()
{
}