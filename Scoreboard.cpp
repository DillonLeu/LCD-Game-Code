#include "Scoreboard.h"

Scoreboard::Scoreboard() {}

void Scoreboard::init()
{
    _x = 34;
    _y = 0;
    _scoreUpdate = 0;
}

void Scoreboard::draw(N5110 &lcd)
{
    sprintf(buffer, "SCORE:%d", _scoreUpdate);
    lcd.printString(buffer, _x, _y);


}

int Scoreboard::update()
{

    _scoreUpdate += 1;
    return _scoreUpdate;

}
