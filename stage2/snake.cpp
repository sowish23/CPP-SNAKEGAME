#include "snake.h"
using namespace std;

Snake::Snake(int r, int c) : row(r), col(c)
	{
		for(int i=0; i<3; i++)
			snake_vec.push_back(Vector(col/2, row/2+i));
		setDirection(0);
		end = false;
		speed = 100000;
		map_list = new char[row*col];
	}

Snake::~Snake(){ delete [] map_list; }

void Snake::setDirection(int d){
	switch(d)
	{
		case 0 : direction = Vector(0, -1); break;
		case 1 : direction = Vector(1, 0); break;
		case 2 : direction = Vector(0, 1); break;
		case 3 : direction = Vector(-1, 0); break;
	}
}

void Snake::moveSnakeHead(){
	snake_vec[0] += direction;
	for(int i=0; i<wall.size(); i++) {
		if(snake_vec[0].getX() == wall[i].getX() && snake_vec[0].getY() == wall[i].getY()) setEnd(true);
	}
}

void Snake::moveSnakeBody(){
	for(unsigned int i=snake_vec.size()-1; i>0; --i) snake_vec[i] = snake_vec[i - 1];
}

char* Snake::setMaptoList(int map[40][60]){
	memset(map_list, ' ', row*col);
	for(unsigned int i=0; i<40; i++) {
		for(int j=0; j<60; j++){
			switch(map[i][j]) {
				case 1 :
					map_list[i*col+j] = '1';
					wall.push_back(Vector(j,i));
					break;
				case 2 : map_list[i*col+j] = '2'; break;
				case 3 : map_list[i*col+j] = '3'; break;
				case 4 : map_list[i*col+j] = '4'; break;
			}
		}

	}
	map_list[snake_vec[0].getY()*col+snake_vec[0].getX()] = 'h';
	for(unsigned int i=1; i<snake_vec.size(); ++i)
		map_list[snake_vec[i].getY()*col+snake_vec[i].getX()] = 'b';
	return map_list;
}

char Snake::getDirection(){
	if(direction.getX()==1) return 'r';
	else if(direction.getX()==-1) return 'l';
	else if(direction.getY()==-1) return 'u';
	else return 'd';
}

void Snake::setEnd(bool e) {end = e;}
bool Snake::getEnd() {return end;}
int Snake::getSpeed() {return speed;}
int Snake::getRow() {return row;}
int Snake::getCol() {return col;}
