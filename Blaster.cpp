#include "Blaster.h"

Blaster::Blaster() {};

void Blaster::init()
{
    _x = 41;
    _y = 39;
    _firingSpeed = 4;
}
void Blaster::draw(N5110 &lcd)
{
    lcd.drawSprite(_x, _y, 3, 1, (int*) _blaster);
}

//When blaster button pressed
void Blaster::update(bool nuclearPlaneCollision, bool supersonicCollision) 
{
    if (nuclearPlaneCollision == false && supersonicCollision == false)
    {
    _y -= _firingSpeed;
    }
    else if (nuclearPlaneCollision == true) 
    {
    _y -= 0;
    }
    else if (supersonicCollision == true)
    {
    _y -= 0;
    }
}

Position2D Blaster::get_pos()
{
    return {_x, _y};
}

void Blaster::set_pos(Position2D p)
{
    printf("Set Blaster Position\n");
    _x = p.x + 5;
    _y = p.y;
    printf("x = %d", _x);
}
