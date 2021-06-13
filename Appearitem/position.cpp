#include "position.h"
using namespace std;


position::position(){
    x = 0;
    y = 0;
}
position::position(int tempx, int tempy){
    x = tempx;
    y = tempy;
}

position& position::randomPosition(){
    // position temp_position(0,0);
    srand(time(NULL));
    this ->x = rand()%60;
    this ->y = rand()%40;
    // if(x==y) randomPosition();
    return *this;
}

// position::position& setPosition(int x_value, int y_value){
//     x = x_value;
//     y = y_value;
//     return *this;
// }

// position::position getPostion()const{
//     return position(this->x, this ->y);
// }

position& position::operator=(const position& v){
    this -> x = v.x;
    this -> y = v.y;
    return *this;
}
bool position::operator==(const position v){
    if((x == v.x) && ( y == v.y))
        return true;
    else
        return false;
}

