#include "Worm.h"
#include "CommonFunc.h"
#include "BaseObject.h"
#include"game_map.h"
#include <string>
#include <iostream>
using namespace std;

#define START_X 9
#define START_Y 4
#define WORM_CELL 52
#define SPEED 1
#define DESTINATION_X 14
#define DESTINATION_Y 4

static int distanceMoved = 0;
static int totalDistance = 0;
void Worm::changePlayGroundState(CellType type)
{
	for (WormNode* cur = head; cur != NULL; cur = cur->next)
	{
		map->getMap().tile[cur->pos.y][cur->pos.x] = type;
	}

}
Worm::Worm(GameMap* map) : map(map) {

	head = new WormNode(Position(START_X, START_Y));


	head->next = new WormNode(Position(START_X - 1, START_Y));
	head->next->next = new WormNode(Position(START_X - 2, START_Y));
	direction = NONE;

}


Worm::~Worm() {}

void Worm::processUserInput(UserInput input)
{
	inputQueue.push(input);
}

bool Worm::checkPosition(Position p)
{
	if (p.x < 0 || p.x >= MAX_MAP_X || p.y < 0 || p.y >= MAX_MAP_Y)
		return false;
	WormNode* cur = head;
	while (cur != NULL)
	{
		if (cur->pos == p)
			return false;
		cur = cur->next;
	}
	return true;
}
//thay doi phuong huong
Direction Worm::changeDirection(UserInput input)
{
	switch (input)
	{
	case KEY_UP:
		if (direction != DOWN)
			return UP;
		break;
	case KEY_DOWN:

		if (direction != UP)
			return DOWN;

		break;
	case KEY_LEFT:
		if (direction != RIGHT)
			return LEFT;
		break;
	case KEY_RIGHT:
		if (direction != LEFT)
			return RIGHT;
		break;
	}
	return direction;
}
//thuc hien buoc tiep theo cua con sau
void Worm::nextStep(Map& map_data, Apple& apple)
{
	if (CheckToFullWorm(map_data, apple))
	{
		WormNode* cur = head;
		while (cur != NULL)
		{
			cur->pos.y += SPEED;
			cur = cur->next;
		}
	}
	else {
		if (distanceMoved < WORM_CELL) {
			static bool eventProcessed = false; // Đánh dấu xem sự kiện đã được xử lý chưa
			if (!inputQueue.empty() && !eventProcessed)
			{
				direction = changeDirection(inputQueue.front());
				inputQueue.pop();
				eventProcessed = true; // Đánh dấu rằng sự kiện đã được xử lý
			}
			else
			{
				eventProcessed = false; // Đặt lại cờ khi không có sự kiện nào hoặc sự kiện đã được xử lý
			}


			// Lưu lại vị trí cũ của đầu
			Position oldHeadPosition = head->pos;
			;
			// Di chuyển đầu của con sâu
			switch (direction)
			{
			case UP:
				if (CheckToMapUp(map_data))
				{
					break;
				}
				else {
					if (checkPosition(Position(head->pos.x, head->pos.y - 1))) {
						head->pos.y -= SPEED;
						if (checkToApple(apple))
						{
							head->pos = oldHeadPosition;
							head = WormNode::insertHead(head, apple.getPos());
							apple.removeApple();
							eatedapple = true;
						}
						
						break;
					}
					break;

				}
			case DOWN:
				if (CheckToMapDown(map_data))
				{
					break;
				}
				else {
					if (checkPosition(Position(head->pos.x, head->pos.y + 1)))
					{
						head->pos.y += SPEED;
						if (checkToApple(apple))
						{
							head->pos = oldHeadPosition;
							head = WormNode::insertHead(head, apple.getPos());
							apple.removeApple();
							eatedapple = true;
						}
						
						break;
					}
					break;
				}
			case LEFT:
				if (CheckToMapLeft(map_data))
				{
					break;
				}
				else {
					if (checkPosition(Position(head->pos.x - 1, head->pos.y))) {
						head->pos.x -= SPEED;
						if (checkToApple(apple))
						{
							head->pos = oldHeadPosition;
							head = WormNode::insertHead(head, apple.getPos());
							apple.removeApple();
							eatedapple = true;
						}
					
						break;
					}
					break;
				}
			case RIGHT:
				if (CheckToMapRight(map_data))
				{
					break;
				}
				else {
					if (checkPosition(Position(head->pos.x + 1, head->pos.y))) {

						head->pos.x += SPEED;
						if (checkToApple(apple))
						{
							head->pos = oldHeadPosition;
							head = WormNode::insertHead(head, apple.getPos());
							apple.removeApple();
							eatedapple = true;
						}
						
						break;
					}
					break;
				}

			}
			distanceMoved += SPEED;
			if (distanceMoved >= WORM_CELL) {
				distanceMoved = 0; // Đặt lại số ô đã di chuyển
			}

			if (eatedapple)
			{
				eatedapple = false;
			}
			else {
				WormNode* current = head->next;
				while (current != nullptr)
				{
					if (oldHeadPosition != head->pos)
					{
						Position temp = current->pos;
						current->pos = oldHeadPosition;
						oldHeadPosition = temp;
						current = current->next;
					}
					else
					{
						break;
					}
				}

			}

		}
		direction = NONE;

	}


}


bool Worm::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{


	}
	else {
		cout << "Khong the load hinh anh" << endl;
	}
	return ret;
}
//ve con sau
void Worm::drawWorm(SDL_Renderer* screen) {
	vector<Position> pos = getWormPosition();
	SDL_Rect rect;
	cout << pos.size() << endl;
	for (size_t i = 0; i < pos.size(); i++)
	{
		string imgPath;
		if (i == 0)
		{
			if (pos[i].y < pos[i + 1].y)
			{
				imgPath = "image//head_up.png";

			}
			else if (pos[i].y > pos[i + 1].y)
			{
				imgPath = "image//head_down.png";
			}
			else if (pos[i].x < pos[i + 1].x)
			{
				imgPath = "image//head_left.png";
			}
			else if (pos[i].x > pos[i + 1].x)
			{
				imgPath = "image//head_right.png";
			}
		}
		else if (i > 0 && i < pos.size() - 1)
		{
			if (pos[i].x < pos[i - 1].x && pos[i].x>pos[i + 1].x)
			{
				imgPath = "image//body_horizontal_right.png";
			}
			else if (pos[i].x > pos[i - 1].x && pos[i].x < pos[i + 1].x)
			{
				imgPath = "image//body_horizontal_left.png";
			}
			else if (pos[i].y < pos[i - 1].y && pos[i].y>pos[i + 1].y)
			{
				imgPath = "image//body_horizontal_down.png";
			}
			else if (pos[i].y > pos[i - 1].y && pos[i].y < pos[i + 1].y)
			{
				imgPath = "image//body_horizontal_up.png";
			}
			else if (pos[i].x > pos[i + 1].x && pos[i].y > pos[i - 1].y)
			{
				imgPath = "image//body_vertical_up1.png";
			}

			else if (pos[i].x > pos[i + 1].x && pos[i].y < pos[i - 1].y)
			{
				imgPath = "image//body_vertical_down.png";
			}
			else if (pos[i].x < pos[i + 1].x && pos[i].y > pos[i - 1].y)
			{
				imgPath = "image//body_vertical_up.png";
			}
			else if (pos[i].x > pos[i - i].x && pos[i].y > pos[i + 1].y)
			{
				imgPath = "image//body_vertical_left.png";

			}
			else if (pos[i].x < pos[i - 1].x && pos[i].y < pos[i + 1].y)
			{
				imgPath = "image//body_vertical_right.png";
			}
			else if (pos[i].x > pos[i - 1].x && pos[i].y < pos[i + 1].y)
			{
				imgPath = "image//body_vertical_left1.png";
			}
			else if (pos[i].x < pos[i - 1].x && pos[i].y > pos[i + 1].y)
			{
				imgPath = "image//body_vertical_right1.png";
			}
			else if (pos[i].x < pos[i + 1].x && pos[i].y < pos[i - 1].y)
			{
				imgPath = "image//body_vertical_down1.png";
			}

		}
		else
		{
			if (pos[i].y < pos[i - 1].y)
			{
				imgPath = "image//tail_down.png";
			}
			else if (pos[i].y > pos[i - 1].y)
			{
				imgPath = "image//tail_up.png";
			}
			else if (pos[i].x < pos[i - 1].x)
			{
				imgPath = "image//tail_right.png";
			}
			else if (pos[i].x > pos[i - 1].x)
			{
				imgPath = "image//tail_left.png";
			}
		}

		if (!LoadImg(imgPath, screen))
		{

			cout << "Khong the load hinh anh" << endl;
			
		}
		rect = { pos[i].x * WORM_CELL + TILE_SIZE - 11, pos[i].y * WORM_CELL - 14, WORM_CELL, WORM_CELL };
		SDL_RenderCopy(screen, p_object, NULL, &rect);

	}

}
vector<Position> Worm::getWormPosition()
{
	vector<Position> pos;
	WormNode* cur = head;
	while (cur != NULL)
	{
		pos.push_back(cur->pos);
		cur = cur->next;
	}
	return pos;
}
//kiem tra va cham voi map
bool Worm::CheckToMapDown(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	WormNode* cur = head;


	x1 = (cur->pos.x * WORM_CELL + 5) / TILE_SIZE;
	x2 = (cur->pos.x * WORM_CELL + WORM_CELL - 5) / TILE_SIZE;
	y1 = cur->pos.y * WORM_CELL / TILE_SIZE;
	y2 = (cur->pos.y * WORM_CELL + WORM_CELL) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (map_data.tile[y2][x2] != 0 && map_data.tile[y2][x1] != 0)
		{
			return true;
		}
	}
	else
	{
		return true;
	}


	return false;
}
bool Worm::CheckToMapUp(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	WormNode* cur = head;


	x1 = ( cur->pos.x* WORM_CELL + 5 ) / TILE_SIZE;
	x2 = (cur->pos.x * WORM_CELL + WORM_CELL - 5) / TILE_SIZE;
	y1 = (cur->pos.y * WORM_CELL - 5) / TILE_SIZE;
	y2 = (cur->pos.y * WORM_CELL + WORM_CELL) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (map_data.tile[y1][x1] != 0 && map_data.tile[y1][x2] != 0)
		{
			return true;
		}
	}
	else
	{
		return true;
	}

	return false;
}

bool Worm::CheckToMapLeft(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	WormNode* cur = head;


	x1 = (cur->pos.x * WORM_CELL - 5) / TILE_SIZE;
	x2 = (cur->pos.x * WORM_CELL + WORM_CELL) / TILE_SIZE;
	y1 = (cur->pos.y * WORM_CELL + 10) / TILE_SIZE;
	y2 = (cur->pos.y * WORM_CELL + WORM_CELL - 5) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (map_data.tile[y1][x1] != 0 && map_data.tile[y2][x1] != 0)
		{
			return true;
		}
	}
	else
	{
		return true;
	}



	return false;
}
bool Worm::CheckToMapRight(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	WormNode* cur = head;


	x1 = cur->pos.x * WORM_CELL / TILE_SIZE;
	x2 = (cur->pos.x * WORM_CELL + WORM_CELL + 5) / TILE_SIZE;
	y1 = cur->pos.y * WORM_CELL / TILE_SIZE;
	y2 = (cur->pos.y * WORM_CELL + WORM_CELL - 5) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (map_data.tile[y1][x2] != 0 && map_data.tile[y2][x2] != 0)
		{
			return true;
		}
	}
	else
	{
		return true;
	}

	return false;
}
bool Worm::CheckToFullWorm(Map& map_data, Apple& apple)
{
	
	WormNode* cur = head;
	while (cur != NULL)
	{
		int x1 = (cur->pos.x * WORM_CELL + 26) / TILE_SIZE;
		int x2 = (cur->pos.x * WORM_CELL + WORM_CELL - 5) / TILE_SIZE;
		int y1 = (cur->pos.y * WORM_CELL + 5) / TILE_SIZE;
		int y2 = (cur->pos.y * WORM_CELL + WORM_CELL) / TILE_SIZE;


		if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x2] != 0 ||
			map_data.tile[y1][x2] != 0 || map_data.tile[y2][x1] != 0 || (cur->pos.y + 1 == apple.getPos().y && cur->pos.x == apple.getPos().x))
		{
			return false; // Có va chạm, trả về false
		}


		cur = cur->next;
		
	}

	return true; // Không có va chạm, trả về true
}
bool Worm::checkToApple(Apple& apple)
{
	WormNode* cur = head;
	if (cur->pos == apple.getPos())
		return true;
	return false;

}
Destination::Destination() : pos(Position(DESTINATION_X, DESTINATION_Y)) {}
bool Destination::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
	}
	else {
		cout << "Khong the load hinh anh" << endl;
	}
	return ret;
}
void Destination::Draw(SDL_Renderer* screen)
{
	if (!LoadImg("image//destination.png", screen))
	{
		cout << "Khong the load hinh anh" << endl;
	}
	SDL_Rect rect = { pos.x * WORM_CELL + TILE_SIZE - 6, pos.y * WORM_CELL - 10, WORM_CELL, WORM_CELL - 5 };
	SDL_RenderCopy(screen, p_object, NULL, &rect);
}
bool Worm::checkToDestination(Destination& destination)
{
	
	WormNode* cur = head;
	if (cur->pos == destination.getPos())
	{
		cout << "huy";
		return true;
	}
	return false;
}
void Worm::drawCompleteLv(SDL_Renderer* screen)
{
	if (!LoadImg("image//completeLv.png", screen))
	{
		cout << "Khong the load hinh anh" << endl;
	}
	SDL_Rect rect = { 200, 5, 854, 540};
	SDL_RenderCopy(screen, p_object, NULL, &rect);
}