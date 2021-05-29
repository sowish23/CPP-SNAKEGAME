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
int Snake::gateDirection(Vector gate, int map[40][60]){
	Vector A = gate + Vector(0,-1) ;
	if(map[A.getY()][A.getX()]==0) return 0;
	Vector B = gate + Vector(1,0) ;
	if(map[B.getY()][B.getX()]==0) return 1;
	Vector C = gate + Vector(0,1) ;
	if(map[C.getY()][C.getX()]==0) return 2;
	Vector D = gate + Vector(-1,0) ;
	if(map[D.getY()][D.getX()]==0) return 3;

	return -1;
}

void Snake::moveSnakeHead(int map[40][60]){
	snake_vec[0] += direction;
	for(int i=0; i<wall.size(); i++) {
		if(snake_vec[0] == wall[i]) {
			if(snake_vec[0] == gate[1]) {
				snake_vec[0].setX(gate[0].getX());
				snake_vec[0].setY(gate[0].getY());
				setDirection(gateDirection(gate[0], map));
				break;
			}
			else if(snake_vec[0] == gate[0]) {
				snake_vec[0].setX(gate[1].getX());
				snake_vec[0].setY(gate[1].getY());
				setDirection(gateDirection(gate[1], map));
				break;
			}
			else setEnd(true);
		}
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
				case 98 : map_list[i*col+j] = '8'; break;
				case 99 : map_list[i*col+j] = '9'; break;
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

void Snake::setGate(int map[40][60]) {
	int randWall = rand() % wall.size();
	int randWall2 = rand() % wall.size();
	if(randWall == randWall2) setGate(map);
	gate[0] = wall[randWall];
	gate[1] = wall[randWall2];
	map[gate[0].getY()][gate[0].getX()] = 98;
	map[gate[1].getY()][gate[1].getX()] = 99;

	// wall.erase(wall.begin() + randWall);
	// wall.erase(wall.begin() + randWall2);
}
 
void Snake::removeGate(int map[40][60]) {
	map[gate[0].getY()][gate[0].getX()] = 1;
	map[gate[1].getY()][gate[1].getX()] = 1;
}
 