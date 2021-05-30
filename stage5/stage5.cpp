#include "snake.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>	//usleep(microseconds);
using namespace std;

char missionB = ' '; //미션 성공여부 표시해주는 캐릭터
char missionGrowth = ' ';
char missionPoison = ' ';
char missionGate = ' ';

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
			int ch;
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
			}
			mvwaddch(win, y, x, ch);
		}
	}
	wrefresh(win);
}

void printScoreBoard(WINDOW* w, int snakeLen, int level, int growthItem, int poisonItem, int Gate){
	werase(w);
	wbkgd(w, COLOR_PAIR(level));
	wborder(w, '|','|','~','~','.','.','.','.');
	mvwprintw(w, 1, 1, "Score Board");
  mvwprintw(w, 2, 1, "B:(CurrentLength)/(Max  Length) %d/%d", snakeLen, snakeMaxLen);
  mvwprintw(w, 3, 1, "+:(GrowthItems Num) ", growthItem);
  mvwprintw(w, 4, 1, "-:(PoisonItems Num) ", poisonItem);
  mvwprintw(w, 5, 1, "G:(Gate Num) ", Gate);
  mvwprintw(w, 6, 1, "Level : %d ", level);
	wrefresh(w);
}

void printMission(WINDOW* w, int level){
  werase(w);
  wbkgd(w, COLOR_PAIR(level));
  wborder(w, '|','|','~','~','.','.','.','.');
  mvwprintw(w, 1, 1, "Mission");
  mvwprintw(w, 2, 1, "B: 10 ( %c )", missionB);
  mvwprintw(w, 3, 1, "+:5  ( %c )", missionGrowth);
  mvwprintw(w, 4, 1, "-:2  ( %c )", missionPoison);
  mvwprintw(w, 5, 1, "G:1  ( %c )" ,missionGate);
  wrefresh(w);
}

void game() {
	float x, y;
  int *map;
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

  WINDOW *scoreBoard = newwin(10, 40, 0,60);
  wrefresh(scoreBoard);
  // nodelay(scoreBoard, TRUE);

  WINDOW *mission = newwin(10, 40, 12,60);
  wrefresh(mission);
  // nodelay(scoreBoard, TRUE);

	Snake snake(40, 60);

	while(!snake.getEnd())
	{
    WINDOW *win1 = newwin(40, 60, 0, 0); //row, col, startY, startX

    printScoreBoard(scoreBoard, snake.getSnakeLen(), snake.getLevel(),snake.poisonItem, snake.growthItem, snake.Gate);
    printMission(mission, snake.getLevel());

    char *map = snake.changeMap();
    wbkgd(win1, COLOR_PAIR(snake.getLevel()));
    wattron(win1, COLOR_PAIR(snake.getLevel()));
    nodelay(win1, TRUE);
    keypad(win1, TRUE);
    refresh();
    wrefresh(win1);
    drawGameMap(win1, snake, map, snake.getRow(), snake.getCol());

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
