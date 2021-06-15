#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>	//usleep(microseconds);

#include "snake.h"
// #include "position.h"
// #include"appearItem.cpp"

// class position;


// #include "appearItem.cpp"
// #pragma once
using namespace std;

extern int map[5][40][60];
extern void appearposion(int stage_num);
extern void appeargrowth(int stage_num);
extern void disappearPoison(int stage_num);
extern void disappeargrowth(int stage_num);
extern void crushItem();
extern vector<Vector> minusSnake();
extern position getHead();
extern vector<position> vpoison_item;
extern vector<position> vgrow_item;
// extern vector<Vector> snake_vec;


char* updateitem(Snake snake, int stage_num,char *map_table);


void newWindow(float y, float x){
    clear();
    initscr();
    noecho();
    getmaxyx(stdscr, y, x);
}

int UserInput(){
    int UserInput = getch();
    refresh();
    endwin();
    clear();
    return UserInput;
}

int startGame(float y, float x) {
    newWindow(y,x);
    printw("Do you want to start snake game? (y/n)");

    return UserInput();
}

int playAgain(float y, float x){
    newWindow(y,x);
    printw("Do you want to play again? (y/n)");
    return UserInput();
}

void drawGameMap(WINDOW* win, Snake& snake, char* table, int row, int col)
{
	werase(win);
	for(int i=0; i<(row*col); i++)
	{
		if(table[i]!=' ')
		{
			int y = i / col;
			int x = i - (y*col);
			char ch;
			int d;
			switch(table[i])
			{
				case '0':
                    ch = ' ';
                    break;
                case '1':
                    ch = '*';
                    break;
                case '2':
                    ch = '+';
                    break;
                case '4':
                    ch = '@';
                    break;
				case 'h':
					ch = '#';
					break;
				case 'b':
					ch = '#';
					break;
				case '3':
                    ch = '0';
                    break;
                case '6':
                    ch = 'x';
                    break;
			}
			mvwaddch(win, y, x, ch);
		}
	}
	wrefresh(win);
}


void game() {

	float x, y;
	initscr();
	noecho();
	cbreak();

	start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_BLUE);

	getmaxyx(stdscr, y, x);
	WINDOW *win1 = newwin(40, 60, 0, 0); //row, col, startY, startX
	Snake snake(40, 60);
	wbkgd(win1, COLOR_PAIR(4));
	wattron(win1, COLOR_PAIR(4));

	nodelay(win1, TRUE);
	keypad(win1, TRUE);
	refresh();
	wrefresh(win1);

	int temp = 0;
	bool itemTemp = 0;
	// char *map_table;

	while(!snake.getEnd()){
		char *map_table = snake.setMaptoList(map[snake.getLevel()-1]);
		drawGameMap(win1, snake, map_table, snake.getRow(), snake.getCol());
		// snake_head.setPosition(snake_vec[0].getX(),snake_vec[0].getY());

		// if(vgrow_item.empty() != 0){ //vector is not empty
		// 	// if(snake.returnValue(0) == vgrow_item.back()){}
		// 	if((snake.returnValue(0).x == vgrow_item.back().x)
		// 	&&(snake.returnValue(0).y == vgrow_item.back().y)){
		// 		disappeargrowth(snake.getLevel());
		// 		snake.plusSnake(snake.returnValue(snake.getSize()-1));
		// 		appeargrowth(snake.getLevel());
		// 	}
		// }
        if(vgrow_item.empty() ==0){
			position head = snake.getHead();
			if(head == vgrow_item.back()){
				snake.crushItem();
			}
		}
		if(vpoison_item.empty() ==0){
			position head = snake.getHead();
			if(head == vpoison_item.back()){
				snake.minusSnake();
			}
		}
		// if(vpoison_item.empty() != 0){ //vector is not empty
		// 	if((snake.returnValue(snake.getSize()-1).x == vpoison_item.back().x)
		// 	&&(snake.returnValue(snake.getSize()-1).y == vpoison_item.back().y)){
		// 		disappearPoison(snake.getLevel());
		// 		snake.minusSnake();
		// 		appeargrowth(snake.getLevel());
		// 	}
		// }

		if(snake.getSize() <3) snake.setEnd(TRUE);

		if(snake.getSize() >6){
			snake.setLevel(snake.getLevel()+1);
			snake.resize(3);
		}
		
		temp ++;
		if(temp >80){
			disappeargrowth(snake.getLevel()-1);
			disappearPoison(snake.getLevel()-1);
			temp = 0;
			appeargrowth(snake.getLevel()-1);
			appearposion(snake.getLevel()-1);
		}	


		int input = wgetch(win1);
		char d = snake.getDirection();
		switch(input)
		{
			case 'w':
			case KEY_UP:
				if(d!='u' && d!='d') snake.setDirection(0);
				else if (d=='d') snake.setEnd(true);
				break;
			case 's':
			case KEY_DOWN:
				if(d!='d' && d!='u') snake.setDirection(2);
				else if (d=='u') snake.setEnd(true);
				break;
			case 'a':
			case KEY_LEFT:
				if(d!='l' && d!='r') snake.setDirection(3);
				else if (d=='r') snake.setEnd(true);
				break;
			case 'd':
			case KEY_RIGHT:
				if(d!='r' && d!='l') snake.setDirection(1);
				else if (d=='l') snake.setEnd(true);
				break;
		}
		snake.moveSnakeBody();
		snake.moveSnakeHead();
		usleep(snake.getSpeed());

	}



}



int main(){
	if (startGame(0, 0) == 'y') {
		do {
			game();
		} while(playAgain(0, 0) == 'y');
	}
	endwin();
	return 0;
}
