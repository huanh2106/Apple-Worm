#ifndef WORM_H_
#define WORM_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include<queue>
class GameMap;

enum UserInput {
	NO_INPUT = 0, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum CellType {
	CELL_EMPTY = 0, CELL_WORM, CELL_APPLE, CELL_STONE
};
struct WormNode
{
	Position pos;
	WormNode* next;
	WormNode(Position position, WormNode* n=NULL) : pos(position), next(n) {}
	static WormNode* insertHead(WormNode* head, Position position)
	{
		WormNode* newHead= new WormNode(position, head);
		return newHead;
	}
	
};

class Worm
{
	WormNode* head;
    GameMap* map;
	Direction dir;
	std::queue<UserInput> inputQueue;
	 
	int apple;
public:
	Worm(GameMap* map);
	~Worm();	
	void processUserInput(UserInput input);
	void nextStep();
	bool checkPosition(Position p);
	WormNode* getHead() const { return head; }
	void setHead(WormNode* h) { head = h; }
	void drawWorm();
	private:
		Direction changeDirection(UserInput input);
		void changePlayGroundState(CellType type);




};

#endif

// Path: AppleWorm/Worm.cpp