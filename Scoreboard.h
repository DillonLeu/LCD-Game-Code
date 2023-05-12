#ifndef SCOREBOARD
#define SCOREBOARD

#include "mbed.h"
#include "N5110.h"
class Scoreboard
{
    public:
    Scoreboard();
    void init();
    void draw(N5110 &lcd);
    int update();


    private:
    int _scoreUpdate;
    int _x;
    int _y;
    char buffer[14];
    
};




#endif
