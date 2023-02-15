#pragma once
#include "Sprites.h"
#include "Textures.h"
#include <fstream>
class Map
{
	LPCWSTR MapFilePath;
	int Map_Rows, Map_Cols;
	int Tile_Rows, Tile_Cols;
	int Tile_Width, Tile_Height;
	int Id;
	int tilemap[300][300];

public:
	Map(int ID, LPCWSTR FilePath_data, int Num_Rows, int  Num_Cols, int Tile_rows, int Tile_cols, int map_width = 16, int map_height = 16);
	~Map();
	void LoadFileMap();
	void LoadMapSprite();
	void Draw();
};
typedef Map* LPMAP;
