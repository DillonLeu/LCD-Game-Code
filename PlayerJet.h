#ifndef PLAYERJET
#define PLAYERJET

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

class PlayerJet
{
public:
    PlayerJet();
    void init();
    void draw(N5110 &lcd);
    void update(UserInput input, bool superSonicPlayerJetCollision);
    Position2D get_pos();
private:
    int _x;
    int _y;
    int _speed;
    bool superSonicPlayerJetCollision;
    const int _playerJet[10][11] = {{0,0,0,0,0,1,0,0,0,0,0}
                                   ,{0,0,0,0,1,1,1,0,0,0,0}
                                   ,{0,0,0,0,1,1,1,0,0,0,0}
                                   ,{0,0,0,1,1,1,1,1,0,0,0}
                                   ,{0,0,0,1,1,1,1,1,0,0,0}
                                   ,{0,0,1,1,0,0,0,1,1,0,0}
                                   ,{0,1,1,0,1,0,1,0,1,1,0}
                                   ,{1,1,1,0,0,0,0,0,1,1,1}
                                   ,{0,0,1,1,1,0,1,1,1,0,0}
                                   ,{0,0,0,1,1,0,1,1,0,0,0}};

};
#endif
