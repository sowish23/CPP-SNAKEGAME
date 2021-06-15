#include <iostream>
#include <vector>
#include "vector.h"
#include <string.h>
#include "position.h"

// #include "appearItem.cpp"
// #pragma once

using namespace std;


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


public:
	Snake(int r, int c);
	~Snake();

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
	int getRow();
	int getCol();
	//fix
	position returnValue(int idx);
	int getSize();
	void setLevel(int new_level);
	vector<Vector> plusSnake(vector<Vector> input);
	vector<Vector> minusSnake();
	void crushItem();
	position getHead();
	void resize(int new_size);
};
