#include "snake.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>	//usleep(microseconds);
using namespace std;

extern int map[5][40][60];
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

char missionB = 'X'; //미션 성공여부 표시해주는 캐릭터
char missionGrowth = 'X';
char missionPoison = 'X';
char missionGate = 'X';

int num_missionB = 6; // 미션 기준
int num_missionGrowth = 2;
int num_missionPoison = 2;
int num_missionGate = 1;


void newWindow(float y, float x){ //새창 만들기
    clear();
    initscr();
    noecho();
    getmaxyx(stdscr, y, x);
}

int UserInput(){ //인풋받기
    int UserInput = getch();
    refresh();
    endwin();
    clear();
    return UserInput;
}

int startGame(float y, float x) { //게임시작
    newWindow(y,x);
    printw("Do you want to start snake game? (y/n)");
    return UserInput();
}

int playAgain(float y, float x){ //게임재시작
    newWindow(y,x);
    printw("Do you want to play again? (y/n)");
    return UserInput();
}

void drawGameMap(WINDOW* win, Snake& snake, char* table, int row, int col) //맵 그리기
{
	werase(win);
	for(int i=0; i<(row*col); i++)
	{
		if(table[i]!=' ')
		{
			int y = i / col;
			int x = i - (y*col);
			int ch;
			switch(table[i])
			{
				case '0': //스네이크가 움직일 수 있는 공간
                    ch = ' ';
                    break;
                case '1': //게이트가 생길 수 있는 벽
                    ch = '*';
                    break;
                case '2': //게이트가 생길 수 없는 벽
                    ch = '+';
                    break;
                case '4': //맵 테두리
                    ch = '@';
                    break;
				case 'h': //snake head
					ch = '#';
					break;
				case 'b': //snake body
					ch = '#';
					break;
				case '8': //gate1 임시표시
					ch = '1';
					break;
				case '9': //gate2 임시표시
					ch = '2';
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

void updateMap(Snake& snake, int map[40][60]) { //일정시간마다 맵 업데이트
	snake.setGate(map); //gate를 임의로 설정
}

void printScoreBoard(WINDOW* w, int snakeLen, int level, int growthItem, int poisonItem, int Gate){
	werase(w);
	wbkgd(w, COLOR_PAIR(level));
	wborder(w, '|','|','~','~','.','.','.','.');
	mvwprintw(w, 1, 1, "Score Board");
  mvwprintw(w, 2, 1, "B:(CurrentLength)/(Max  Length) %d/%d", snakeLen, snakeMaxLen);
  mvwprintw(w, 3, 1, "+:(GrowthItems Num): %d ", growthItem);
  mvwprintw(w, 4, 1, "-:(PoisonItems Num): %d ", poisonItem);
  mvwprintw(w, 5, 1, "G(Number of Entered Gate) : %d ", Gate);
  mvwprintw(w, 6, 1, "Level : %d ", level);
	wrefresh(w);
}

void printMission(WINDOW* w, int level){
  werase(w);
  wbkgd(w, COLOR_PAIR(level));
  wborder(w, '|','|','~','~','.','.','.','.');
  mvwprintw(w, 1, 1, "Mission");
  mvwprintw(w, 2, 1, "B: 6 ( %c )", missionB);
  mvwprintw(w, 3, 1, "+: 2  ( %c )", missionGrowth);
  mvwprintw(w, 4, 1, "-: 2  ( %c )", missionPoison);
  mvwprintw(w, 5, 1, "G: 1  ( %c )" ,missionGate);
  wrefresh(w);
}

void setMission(Snake& snake){
  if(vgrow_item.empty() ==0){
    position head = snake.getHead();
    if(head == vgrow_item.back()){
      snake.crushItem();
      snake.changeSnakeLen();
      snake.growthItem++;
    }
  }
  if(vpoison_item.empty() ==0){
    position head = snake.getHead();
    if(head == vpoison_item.back()){
      snake.minusSnake();
      snake.changeSnakeLen();
      snake.poisonItem++;
    }
  }
  if(snake.getSize() == num_missionB) {missionB ='O';}
  if(snake.growthItem == num_missionGrowth) {missionGrowth = 'O';}
  if(snake.poisonItem == num_missionPoison) {missionPoison = 'O';}
  if(snake.getGateCnt() == num_missionGate) {missionGate = 'O';}
}

void nextLevel(Snake& snake){
  if((missionB == 'O')&&(missionGate=='O')&&(missionGrowth=='O')&&(missionPoison=='O')){
    snake.resize(3);
    snake.growthItem =0;
    snake.poisonItem =0;
    snake.setGateCnt(0);
    snake.setLevel(snake.getLevel()+1);
  }
}

void game() { //game 실행

	float x, y;
	initscr();
	noecho();
	cbreak();

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);

	getmaxyx(stdscr, y, x);
	WINDOW *win1 = newwin(40, 60, 0, 0); //row, col, startY, startX
  WINDOW *scoreBoard = newwin(10, 40, 0,60);
  wrefresh(scoreBoard);
  // nodelay(scoreBoard, TRUE);

  WINDOW *mission = newwin(10, 40, 12,60);
  wrefresh(mission);
  // nodelay(scoreBoard, TRUE);

	Snake snake(40, 60);
	// wbkgd(win1, COLOR_PAIR(1));
	// wattron(win1, COLOR_PAIR(1));
  //
	// nodelay(win1, TRUE);
	// keypad(win1, TRUE);
	// refresh();
	// wrefresh(win1);
	int mapCnt = 0;
	while(!snake.getEnd()) //exit가 true가 될때까지 반복문
	{
	WINDOW *win1 = newwin(40, 60, 0, 0); //row, col, startY, startX
	printScoreBoard(scoreBoard, snake.getSnakeLen(), snake.getLevel(), snake.growthItem, snake.poisonItem, snake.getGateCnt());
	printMission(mission, snake.getLevel());

	srand(time(NULL)); //랜덤 씨드값 설정
	char *map_table = snake.setMaptoList(map[snake.getLevel()-1]);//2차원 배열 맵을 리스트로 변환함
	wbkgd(win1, COLOR_PAIR(snake.getLevel()));
	wattron(win1, COLOR_PAIR(snake.getLevel()));
	nodelay(win1, TRUE);
	keypad(win1, TRUE);
	refresh();

	wrefresh(win1);
		drawGameMap(win1, snake, map_table, snake.getRow(), snake.getCol()); //draw함수 호출하여 맵 업데이트
    setMission(snake);
		if (mapCnt == 0) {
			(snake, map[snake.getLevel()-1]); //처음 맵 설정
		}
		mapCnt+= 1;
		if (mapCnt == 100) { //10초마다 맵 업데이트
			snake.removeGate(map[snake.getLevel()-1]);
			updateMap(snake, map[snake.getLevel()-1]);
			mapCnt = 1;
			disappeargrowth(snake.getLevel()-1);
			disappearPoison(snake.getLevel()-1);
			appeargrowth(snake.getLevel()-1);
			appearposion(snake.getLevel()-1);
		}

		int input = wgetch(win1); //키 입력받기
		char d = snake.getDirection(); //snake의 방향 설정
		switch(input)
		{
			case 'w':
			case KEY_UP: //키가 w거나 윗방향키일때
				if(d!='u' && d!='d') snake.setDirection(0); //방향이 위거나 아래가 아닌 경우에 방향을 바꿈
				else if (d=='d') snake.setEnd(true); //아랫방향일 경우 입력을 받게 되면 exit을 true로 변경
				break;
			case 's':
			case KEY_DOWN: //키가s거나 아랫방향키일떄
				if(d!='d' && d!='u') snake.setDirection(2);
				else if (d=='u') snake.setEnd(true);
				break;
			case 'a':
			case KEY_LEFT: //키가 a거나 왼쪽 방향키일때
				if(d!='l' && d!='r') snake.setDirection(3);
				else if (d=='r') snake.setEnd(true);
				break;
			case 'd':
			case KEY_RIGHT: //키가 d이거나 오른쪽 방향키일때
				if(d!='r' && d!='l') snake.setDirection(1);
				else if (d=='l') snake.setEnd(true);
				break;
			case 'r' :
			case 'R' :
				snake.setEnd(true);
				snake.removeGate(map[snake.getLevel()]);
				game();
		}
		if(snake.getSize() <3) snake.setEnd(TRUE); //snake 길이 3보다 작으면 끝

		snake.moveSnakeBody(); //body도 함께 바꾸어줌
		snake.moveSnakeHead(map[snake.getLevel()-1]); //head의 방향 변경
    nextLevel(snake); // 레벨 올리기
		usleep(snake.getSpeed()); //speed 설정한 만큼 화면 유지 (=스피드)
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
