#include "vector.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
using namespace std;

#ifdef WIN32 ///For the sleep()
#include <windows.h>	//Sleep(miliseconds);
#else
#include <unistd.h>	//usleep(microseconds);
#endif

class Snake{
	private:
    int width;
    int height;
		int speed;
		vector<Vector> body;
	public:
		Snake(int w, int h):width(w),height(h){
			body.push_back(Vector(w/2, h/2));
			speed=50;
		}
		~Snake(){}

  };

float x,y;

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
int startGame(){
    newWindow(y,x);
    printw("Do you want to start snake game? (y/n)");

    return UserInput();
}
int playAgain(){
    newWindow(y,x);
    printw("Do you want to play again? (y/n)");
    return UserInput();
}


void draw(Snake& snake){
  newWindow(y,x);
}

int main(){
  if (startGame() == 'y'){
    do{
      Snake snake(x-2,y-5);
      draw(snake);
    }while(playAgain()=='y');
  }
  endwin();
  return 0;
}
