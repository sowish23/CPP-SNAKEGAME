#include <iostream>
#include <vector>
#include "vector.h"
#include <string.h>
#include <cstdlib>
using namespace std;

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
public:
	Snake(int r, int c);
	~Snake();

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
	void setGate(int map[40][60]);
	void removeGate(int map[40][60]);
};
