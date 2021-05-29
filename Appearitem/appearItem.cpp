// #pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

// #include "vector.h"
#include "../map.h"
using namespace std;

extern int map[5][40][60];

class position{ //그냥 x,y좌표 반환
public:
    int x,y;
    position(int tempx, int tempy){
        x = tempx;
        y = tempy;
    }

    position& randomPosition(){
        // position poison_position(0,0);
        position temp_position(0,0);
        srand(time(NULL)+rand());
        // poison_position.x = rand()%40; 
        // poison_position.y = rand()%60;
        this -> x = rand()%36 +2;
        this -> y = rand()%56 +2;
        return *this;
    }
    position& operator=(const position& v){
        this -> x = v.x;
        this -> y = v.y;
        return *this;
    }
};


// time_t start_item;
// time_t end_item;
vector<position> vgrow_item;
vector<position> vpoison_item;
position poison_position(0,0);
position growth_position(0,0);

// class checkTime{ //시간 반환
// public:
//     time_t temptime;
//     checkTime(){
//         temptime = time(NULL);
//     }

//     time_t getTemptime(){
//         return temptime;
//     }

    // time_t strat_time(){
    //     start_item = time(NULL);
    //     return start_item;
    // }
    // time_t end_time(){
    //     end_item = time(NULL);
    //     return end_item;
    // }

// };

//--------------------------------------------------------------

// position positionItem(int stage_num){ //랜덤한 좌표 생성
//     int tempx =0;
//     int tempy =0;
//     srand((unsigned int)time(NULL));

//     position temp(tempx,tempy);
//     while(1){
//         if(map[stage_num][tempx][tempy] != 0){
//             tempx = rand()%max_x; 
//             tempy = rand()%max_y;
//         }
//         break;  
//     }
//     position growth_position()
//     vgrow_item.push_back(growth_position);
//     vpoison_item.push_back(poison_position);
//     // return position(tempx,tempy);      
// }

// void itemTimer(int stage_num){ //시간 반환
//     while(item_wait >0)
//     if(item_wait % 10 == 0){
//         position poison_position = positionItem(stage_num);
//         position growth_position = positionItem(stage_num);
//         appearItem(growth_position,poison_position,stage_num);
//     }
//     item_wait--;
// }

void updateMap(int stage_num){
    position poison_position = vpoison_item.back();
    position growth_position = vgrow_item.back();
    map[stage_num][poison_position.x][poison_position.y] = 6;
    map[stage_num][growth_position.x][growth_position.y] = 3;
}

void appearItem(int stage_num){ 
    while(1){
        if((map[stage_num][growth_position.randomPosition().x][growth_position.randomPosition().y] == 0) 
        && (map[stage_num][poison_position.randomPosition().x][poison_position.randomPosition().y] == 0)){
            break;
        }
        else{
            growth_position.randomPosition();
            poison_position.randomPosition();
        }
    }
    vgrow_item.push_back(growth_position);
    vpoison_item.push_back(poison_position);
    updateMap(stage_num);
}



void draw(WINDOW *win, int stage_num) {
    string ch;
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
                case 6:
                    ch = "O";
                    break;
                case 3:
                    ch = "X";
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
        // for(int j=0; i<10; j++){
        //     appearItem(i);
        //     draw(win, i);
        // }
        appearItem(i);
        // appearItem(i);
        draw(win, i);
        // usleep(300000);
        wrefresh(win);
        getch();
        delwin(win);
    }


    endwin();
return 0; }