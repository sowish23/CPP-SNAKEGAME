// need 5file
#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>
#include "position.h"
// #include "../stage2/map.cpp"
// #pragma once

using namespace std;

extern int map[5][40][60];
extern WINDOW *win1;
// #ifdef position
// class position
// #endif



vector<position> vgrow_item ;
vector<position> vpoison_item;
position poison_position(0,0);
position growth_position(0,0);



void update(int stage_num){
    poison_position = vpoison_item.back();
    growth_position = vgrow_item.back();
    map[stage_num][poison_position.y][poison_position.x] = 6;
    map[stage_num][growth_position.y][growth_position.x] = 3;
}

void updategrowth(int stage_num){
    growth_position = vgrow_item.back();
    map[stage_num][growth_position.y][growth_position.x] = 3;
}
void updateposion(int stage_num){
    poison_position = vpoison_item.back();
    map[stage_num][poison_position.y][poison_position.x] = 6;
}

void appearItem(int stage_num){ 
    while(1){
        if((map[stage_num][growth_position.randomPosition().y][growth_position.randomPosition().x] == 0) 
        && (map[stage_num][poison_position.randomPosition().y][poison_position.randomPosition().x] == 0)){
            break;
        }
        else{
            growth_position.randomPosition();
            poison_position.randomPosition();
        }
    }
}
// void appearItem(int stage_num){ 
//     while(1){
//         if((map[stage_num][growth_position.randomPosition().y][growth_position.randomPosition().x] == 0) 
//         && (map[stage_num][poison_position.randomPosition().y][poison_position.randomPosition().x] == 0)){
//             break;
//         }
//         else{
//             growth_position.randomPosition();
//             poison_position.randomPosition();
//         }
//     }

//     vgrow_item.push_back(growth_position);
//     vpoison_item.push_back(poison_position);
//     updategrowth(stage_num);
//     updateposion(stage_num);
//     // update(stage_num);

// }
void appearposion(int stage_num){ 
    while(1){
        // nodelay(win1, TRUE);
        if(map[stage_num][poison_position.randomPosition().y][poison_position.randomPosition().x] != 0){
            poison_position.randomPosition();
        }
        else break;
    }
    vpoison_item.push_back(poison_position);
    updateposion(stage_num);
    // update(stage_num);

}

void appeargrowth(int stage_num){ 
    while(1){
        // nodelay(win1, TRUE);
        if(map[stage_num][growth_position.randomPosition().y][growth_position.randomPosition().x] != 0){
            growth_position.randomPosition();
        }
        else break;
    }

    vgrow_item.push_back(growth_position);
    updategrowth(stage_num);
    // update(stage_num);

}

void disappearPoison(int stage_num){
    if(vpoison_item.empty() == 0 ){
        poison_position = vpoison_item.back();
        map[stage_num][poison_position.y][poison_position.x] = 0;
        vpoison_item.pop_back();
    }
}

void disappeargrowth(int stage_num){
    if(vgrow_item.empty() == 0 ){
        growth_position = vgrow_item.back();
        map[stage_num][growth_position.y][growth_position.x] = 0;
        vgrow_item.pop_back();
    }
}
