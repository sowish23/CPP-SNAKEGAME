#include <iostream>
#include <vector>
#include "vector.h"
#include <string.h>
using namespace std;

const int snakeMaxLen=10;

class Snake
{
private:
	vector<Vector> snake_vec;
	Vector direction;
	const int row, col;
	vector<Vector> wall;
	bool end;
	int speed;
	char* map_list;
	int level;
	int snakeLen;
public:
	Snake(int r, int c);
	~Snake();
	int growthItem, poisonItem, Gate;

	void setDirection(int d);
	void moveSnakeHead();
	void moveSnakeBody();
	char* setMaptoList(int map[40][60]);
	char* changeMap();
	char getDirection();
	void setEnd(bool e);
	bool getEnd();
	int getLevel();
	int getSpeed();
	int getSnakeLen();
	int getRow();
	int getCol();
};
