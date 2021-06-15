#include <iostream>
#include <vector>
#include "vector.h"
#include <string.h>
#include <cstdlib>
#include "position.h"
using namespace std;

const int snakeMaxLen=6;

class Snake
{
private:
	vector<Vector> snake_vec;
	Vector direction;
	const int row, col;
	vector<Vector> wall;
	Vector gate[2];
	bool end;
	int speed;
	char* map_list;
	int gateCnt;
	int level;
	int snakeLen;
public:
	Snake(int r, int c);
	~Snake();
	int growthItem=0;
	int poisonItem=0;

	void setDirection(int d);
	void moveSnakeHead(int map[40][60]);
	void moveSnakeBody();
	char* setMaptoList(int map[40][60]);
	int gateDirection(Vector gate, int map[40][60]);
	char getDirection();
	void setEnd(bool e);
	bool getEnd();
	int getSpeed();
	int getRow();
	int getCol();
	//gate
	void setGate(int map[40][60]);
	void removeGate(int map[40][60]);
	void setGateCnt(int i);
	int getGateCnt();
	int getLevel();
	int getSnakeLen();
	//item
	int getSize();
	void setLevel(int new_level);
	vector<Vector> minusSnake();
	void crushItem();
	position getHead();
	void resize(int new_size);
	void changeSnakeLen();
};
