#include <ncurses.h>
#include <string>
#include "../map.h"


void draw(WINDOW *win, int stage_num) {
    std::string ch;
    for (int i = 0; i<40; i++) {
        for(int j = 0; j < 60; j++){
            switch(map[stage_num][i][j]) {
                case 0:
                    ch = ' ';
                    break;
                case 1:
                    ch = "*";
                    break;
                case 2:
                    ch = "+";
                    break;
                case 4:
                    ch = "■";
                    break;
            }
            const char * c = ch.c_str();
            mvwaddstr(win, i, j, c);
        }
    }

}


int main() {
    // WINDOW *win1;
    // WINDOW *win2;
    WINDOW *win;

    
    initscr();

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_BLUE);
    
    refresh(); 

    for(int i=0; i<5; i++){
        win = newwin(40, 60, 0, 0);
        wbkgd(win, COLOR_PAIR(i+1));
        wattron(win, COLOR_PAIR(i+1));
        // wbkgd(win, COLOR_PAIR(getstage_num()-1));
        // wattron(win, COLOR_PAIR(getstage_num()-1));
        // draw(win, map[getstage_num()-1] ); // stage구현시 getstage_num으로 구현
        draw(win, i);
        wrefresh(win);
        getch();
        delwin(win);
    }


    endwin();
return 0; }