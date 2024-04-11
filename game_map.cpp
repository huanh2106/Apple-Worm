#include"game_map.h"
#include"BaseObject.h"
#include"CommonFunc.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
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

	int val;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			file >> val;
			if (val > 0) {
				if (j > game_map_.max_x) {
					game_map_.max_x = j;
				}
				if (i > game_map_.max_y) {
					game_map_.max_y = i;
				}
			}
			game_map_.tile[i][j] = val;
		}
	}

	file.close();

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
		file.close();

		if (!tile_mat[i].LoadImg(fileName, screen))
		{
			std::cout << "Khong the tai anh: " << fileName << std::endl;
		}
	}
}



  void GameMap::DrawMap1(SDL_Renderer* screen)
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
			if (val > 0 && val < MAX_TILES&& val!=9&&val!=2&&val!=6&&val!=4&&val!=3)
			{
				int x = j * TILE_SIZE;
				int y = i * TILE_SIZE;
				SDL_Rect renderQuad = { x, y, TILE_SIZE, TILE_SIZE };
				SDL_RenderCopy(screen, tile_mat[val].GetObject(), NULL, &renderQuad);
			}
		}
	}
	
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			int val = game_map_.tile[i][j];
			if (val== 9||val==3)
			{
				int x = j * TILE_SIZE;
				int y = i * TILE_SIZE;
				SDL_Rect renderQuad = { x, y, TILE_SIZE/2, TILE_SIZE };
				SDL_RenderCopy(screen, tile_mat[val].GetObject(), NULL, &renderQuad);
			}
		}
	}

}
  
  void GameMap::DrawMap2(SDL_Renderer* screen)
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
			  if (val == 2 || val == 6 || val == 4)
			  {
				  int x = j * TILE_SIZE;
				  int y = i * TILE_SIZE;
				  SDL_Rect renderQuad = { x, y, TILE_SIZE, TILE_SIZE };
				  SDL_RenderCopy(screen, tile_mat[val].GetObject(), NULL, &renderQuad);
			  }
			  if (val == 9)
			  {
				  if (!LoadImg("map/09_2.png", screen))
				  {
					  cout << "Khong the load hinh anh" << std::endl;
				  }
				  int x = j * TILE_SIZE + TILE_SIZE / 2;
				  int y = i * TILE_SIZE;
				  SDL_Rect dst = { x, y, TILE_SIZE / 2, TILE_SIZE };
				  SDL_RenderCopy(screen, p_object, NULL, &dst);
			  }
			  if (val == 3)
			  {
				  if (!LoadImg("map/03_2.png", screen))
				  {
					  cout << "Khong the load hinh anh" << std::endl;
				  }
				  int x = j * TILE_SIZE + TILE_SIZE / 2;
				  int y = i * TILE_SIZE;
				  SDL_Rect dst = { x, y, TILE_SIZE / 2, TILE_SIZE };
				  SDL_RenderCopy(screen, p_object, NULL, &dst);
			  }

		  }
	  }

  }
