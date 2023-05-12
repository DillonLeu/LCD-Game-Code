#include "PlayerJet.h"

PlayerJet::PlayerJet() {};

//initialize playerjet position and size of player jet in sprite [8,9]
void PlayerJet::init() 
{
    //printf("PlayerJet: Init\n");
    _x = 37;
    _y = 40;
}

void PlayerJet::draw(N5110 &lcd) {
    //printf("PlayerJet: Draw\n");
    lcd.drawSprite(_x, _y, 10, 11, (int*) _playerJet);
}

void PlayerJet::update(UserInput input, bool superSonicPlayerJetCollision)
{
    if (superSonicPlayerJetCollision == false)
    {
        //printf("PlayerJet: Update\n");
        //move playerjet by detecting the diretion of the joystick
        _speed = 4;
        if (input.d == N) { _y -= _speed; }
        else if (input.d == S) { _y += _speed; }
        else if (input.d == W) { _x -= _speed; }
        else if (input.d == E) { _x += _speed; }
        else if (input.d == NE) { _y -= _speed; _x += _speed; }
        else if (input.d == NW) { _y -= _speed; _x -= _speed; }
        else if (input.d == SE) { _y += _speed; _x += _speed; }
        else if (input.d == SW) { _y += _speed; _x -= _speed; }
        else if (input.d == CENTRE) {_y = _y + 0; _x = _x + 0; }
        
        //set boundary for the playerjet
        if ( _y < 1) { _y = 1; }
        if ( _y > 37) { _y = 37; }
        if ( _x < 1) { _x = 1; }
        if ( _x > 75) { _x = 75; }
    }
    else if (superSonicPlayerJetCollision == true)
    {
        _speed = 0;
    }
}

Position2D PlayerJet::get_pos() { return {_x, _y}; }  
    

