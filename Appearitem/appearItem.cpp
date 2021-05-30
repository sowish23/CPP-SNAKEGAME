// need 5file
#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

// #include "../stage2/map.cpp"
// #include "../stage2/snake.cpp"
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
        position temp_position(0,0);
        srand(time(NULL));
        this -> x = rand()%60;
        this -> y = rand()%40;
        // if(x==y) randomPosition();
        return *this;
    }
    position& operator=(const position& v){
        this -> x = v.x;
        this -> y = v.y;
        return *this;
    }
};



vector<position> vgrow_item;
vector<position> vpoison_item;
position poison_position(0,0);
position growth_position(0,0);



void update(int stage_num){
    position poison_position = vpoison_item.back();
    position growth_position = vgrow_item.back();
    map[stage_num][poison_position.y][poison_position.x] = 6;
    map[stage_num][growth_position.y][growth_position.x] = 3;
}

void updategrowth(int stage_num){
    position growth_position = vgrow_item.back();
    map[stage_num][growth_position.y][growth_position.x] = 3;
}
void updateposion(int stage_num){
    position poison_position = vpoison_item.back();
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
        if(map[stage_num][growth_position.randomPosition().y][growth_position.randomPosition().x] != 0){
            growth_position.randomPosition();
        }
        else break;
    }

    vgrow_item.push_back(growth_position);
    updategrowth(stage_num);
    // update(stage_num);

}

