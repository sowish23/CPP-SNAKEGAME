#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

class position{ //그냥 x,y좌표 반환
public:
    int x;
    int y;
    position();
    position(int tempx, int tempy);
    position& randomPosition();
    // position& setPosition(int x_value, int y_value);
    // position getPostion();
    position& operator=(const position& v);
    bool operator==(const position v);
};

