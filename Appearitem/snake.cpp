#include "snake.h"
// #include "appearItem.cpp"
// #include "position.h"
// #pragma once

using namespace std;
extern int map[5][40][60];
extern void appearposion(int stage_num);
extern void appeargrowth(int stage_num);
extern void disappearPoison(int stage_num);
extern void disappeargrowth(int stage_num);
// extern vector<position> vpoison_item;
// extern vector<position> vgrow_item;
// #ifdef position
// class position;
// #endif


Snake::Snake(int r, int c) : row(r), col(c)
	{
		for(int i=0; i<3; i++)
			snake_vec.push_back(Vector(col/2, row/2+i));
		setDirection(0);
		end = false;
		speed = 100000;
		map_list = new char[row*col];
		level=1;
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
				case 0 : map_list[i*col+j] = '0'; break;
				case 1 :
					map_list[i*col+j] = '1';
					wall.push_back(Vector(j,i));
					break;
				case 2 : map_list[i*col+j] = '2'; break;
				case 3 : map_list[i*col+j] = '3'; break;
				case 4 : map_list[i*col+j] = '4'; break;
				case 6 : map_list[i*col+j] = '6'; break;
			}
		}

	}
	map_list[snake_vec[0].getY()*col+snake_vec[0].getX()] = 'h';
	for(unsigned int i=1; i<snake_vec.size(); ++i)
		map_list[snake_vec[i].getY()*col+snake_vec[i].getX()] = 'b';
	return map_list;
}

// char* Snake::changeMap(){ // 맵바꾸기
//     if (level == 1){return setMaptoList(map[level]);}
//     else if (level == 2){return setMaptoList(map[level]);}
// 	else if (level == 3){return setMaptoList(map[level]);}
//     else if (level == 4){return setMaptoList(map[level]);}
// 	else if (level == 5){return setMaptoList(map[level]);}
// }

char Snake::getDirection(){
	if(direction.getX()==1) return 'r';
	else if(direction.getX()==-1) return 'l';
	else if(direction.getY()==-1) return 'u';
	else return 'd';
}

void Snake::setEnd(bool e) {end = e;}
bool Snake::getEnd() {return end;}
int Snake::getSpeed() {return speed;}
int Snake::getLevel() {return level;}
int Snake::getRow() {return row;}
int Snake::getCol() {return col;}


position Snake::returnValue(int idx){
	position temp(0,0);
	temp.x = snake_vec[idx].getX();
	temp.y = snake_vec[idx].getY();
	return temp;
}

int Snake::getSize(){return snake_vec.size();}
void Snake::setLevel(int new_level){
	level = new_level; 
}

// position Snake::getHead(){
// 	return snake_head;}

// vector<Vector> Snake::plusSnake(vector<Vector> input){
// 	snake_vec.push_back(input);
// 	return snake_vec;
// }
vector<Vector> Snake::minusSnake(){
	disappearPoison(level-1);
	snake_vec.pop_back();
	appearposion(level-1);
	return snake_vec;
}
void Snake::crushItem(){

	disappeargrowth(level -1);
	snake_vec.push_back(snake_vec.back());
	appeargrowth(level-1);

}
position Snake::getHead(){
	position head(snake_vec[0].getX(),snake_vec[0].getY());
	return head;
}

void Snake::resize(int new_size){
	snake_vec.resize(new_size);
}
