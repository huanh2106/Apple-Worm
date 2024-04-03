#include"game_map.h"
#include"BaseObject.h"
#include"CommonFunc.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

Tilemat::Tilemat()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object = NULL;
}
void GameMap::LoadMap(std::string name) {
	std::ifstream file(name, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Khong the mo tap tin: " << name << std::endl;
		return;
	}

	
	std::vector<std::vector<int>> mapData(MAX_MAP_Y, std::vector<int>(MAX_MAP_X, 0));

	
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			file >> mapData[i][j];
			int val = mapData[i][j];
			if (val > 0) {
				if (j > game_map_.max_x) {
					game_map_.max_x = j;
				}
				if (i > game_map_.max_y) {
					game_map_.max_y = i;
				}
			}
		}
	}

	file.close();
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			game_map_.tile[i][j] = mapData[i][j];
		}
	}

	game_map_.max_x = (game_map_.max_x + 1) * TILE_SIZE;
	game_map_.max_y = (game_map_.max_y + 1) * TILE_SIZE;
	game_map_.start_x = 0;
	game_map_.start_y = 0;
	game_map_.file_name_ = name;
}




void GameMap::LoadTiles(SDL_Renderer* screen)
{
	for (int i = 0; i < MAX_TILES; i++)
	{
		std::string index = std::to_string(i);
		if (i < 10)
		{
						index = "0" + index;
		}
		
		std::string fileName = "map/" + index + ".png";
		std::ifstream file(fileName);
		if (!file.is_open())
		{
			continue;
		}
		

		if (!tile_mat[i].LoadImg(fileName, screen))
		{
			std::cout << "Khong the tai anh: " << fileName << std::endl;
		}
	}
}



  void GameMap::DrawMap(SDL_Renderer* screen)
{

	int mapWidth = MAX_MAP_X * TILE_SIZE;
	int mapHeight = MAX_MAP_Y * TILE_SIZE;

	
	int x1 = 0;
	int x2 = SCREEN_WIDTH;
	int y1 = 0;
	int y2 = SCREEN_HEIGHT;

	
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			int val = game_map_.tile[i][j];
			if (val > 0 && val < MAX_TILES)
			{
				int x = j * TILE_SIZE;
				int y = i * TILE_SIZE;
				SDL_Rect renderQuad = { x, y, TILE_SIZE, TILE_SIZE };
				SDL_RenderCopy(screen, tile_mat[val].GetObject(), NULL, &renderQuad);
			}
		}
	}
}
  
/*void GameMap::GenerateApple()
{
	int x = 10;
	int y = 10;
	while (game_map_.tile[y][x] != CELL_EMPTY)
	{
		x = rand() % MAX_MAP_X;
		y = rand() % MAX_MAP_Y;
	}
	game_map_.tile[y][x] = CELL_APPLE;
}
void GameMap::setCell(Position p, CellType type)
{
	game_map_.tile[p.y][p.x] = type;
}

void GameMap::DrawApple(SDL_Renderer* screen)
{
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			if (game_map_.tile[i][j] == CELL_APPLE)
			{
				int x = j * TILE_SIZE;
				int y = i * TILE_SIZE;
				tile_mat[1].SetRect(x, y);
				SDL_Rect* clip = NULL;
				SDL_Rect renderQuad = { x, y, TILE_SIZE, TILE_SIZE };
				SDL_RenderCopy(screen, tile_mat[1].GetObject(), clip, &renderQuad);
			}
		}
	}
}
*/