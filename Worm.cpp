    #include "Worm.h"
    #include "CommonFunc.h"
    #include "BaseObject.h"
#include"game_map.h"
    #include <string>
#define START_X 10
#define START_Y 10
Worm::Worm(GameMap* map) : map(map), dir(NONE), apple(0)
{
	head = new WormNode(Position(START_X, START_Y));
}
Worm::~Worm() {}
void Worm::processUserInput(UserInput input)
{
	if (input == NO_INPUT)
		return;
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
Direction Worm::changeDirection(UserInput input)
{
	switch (input)
	{
	case KEY_UP:
		if (dir != DOWN)
			return UP;
		break;
	case KEY_DOWN:
		if (dir != UP)
			return DOWN;
		break;
	case KEY_LEFT:
		if (dir != RIGHT)
			return LEFT;
		break;
	case KEY_RIGHT:
		if (dir != LEFT)
			return RIGHT;
		break;
	}
	return dir;
}
void Worm::nextStep()
{
	if (!inputQueue.empty())
	{
		dir = changeDirection(inputQueue.front());
		inputQueue.pop();
	}
	Position nextPos = head->pos;
	switch (dir)
	{
	case UP:
		nextPos.y--;
		break;
	case DOWN:
		nextPos.y++;
		break;
	case LEFT:
		nextPos.x--;
		break;
	case RIGHT:
		nextPos.x++;
		break;
	}
	if (checkPosition(nextPos))
	{
		head = WormNode::insertHead(head, nextPos);
		changePlayGroundState(CELL_WORM);
		if (apple == 0)
		{
			map->GenerateApple();
			apple = 1;
		}
		else
		{
			map->clearApple();
		}
	}
	else
	{
		map->gameOver();
	}
}

void Worm::changePlayGroundState(CellType type)
{
	WormNode* cur = head;
	while (cur != NULL)
	{
		map->setCell(cur->pos, type);
		cur = cur->next;
	}
}

