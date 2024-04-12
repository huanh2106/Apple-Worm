#ifndef WORM_H_
#define WORM_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include"Apple.h"
#include<queue>



enum UserInput {
	NO_INPUT = 0, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum CellType{
	CELL_EMPTY = 0, CELL_WORM=12, CELL_APPLE=13, CELL_STONE=14
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

class Destination : public BaseObject
{
	Position pos;
public:
	Destination();
	~Destination() {}
	Position getPos() const { return pos; }
	void setPos(const Position& newPos) { pos = newPos; }
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Draw(SDL_Renderer* screen);


};
class Worm : public BaseObject 
{
	WormNode* head;
    GameMap* map;
	Direction direction;
	std::queue<UserInput> inputQueue;
	

	
public:
	Worm(GameMap* map);
	~Worm();	
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void processUserInput(UserInput input);
	void nextStep(Map &map_data, Apple &apple);
	bool checkPosition(Position p);
	WormNode* getHead() const { return head; }
	bool CheckToMapDown(Map& map_data);
    bool CheckToMapUp(Map& map_data);
	bool CheckToMapLeft(Map& map_data);
	bool CheckToMapRight(Map& map_data);
	bool checkToApple(Apple& apple);
	void drawCompleteLv(SDL_Renderer* screen);
	bool checkToDestination(Destination& destination);
	void setHead(WormNode* h) { head = h; }
	void SetWorm(const Position &p) {
		head = new WormNode(Position(p.x, p.y));
		head->next = new WormNode(Position(p.x-1,p.y));
		head->next->next = new WormNode(Position(p.x-2, p.y));
	}
	
	void drawWorm(SDL_Renderer* screen);
	bool CheckToFullWorm(Map& map_data, Apple &apple);
	
	bool eatedapple = false;
	std::vector<Position> getWormPosition();

	private:
		Direction changeDirection(UserInput input);
		void changePlayGroundState(CellType type);
};


#endif

// Path: AppleWorm/Worm.cpp