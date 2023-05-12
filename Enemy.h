#ifndef ENEMY
#define ENEMY

#include "N5110.h"
#include "mbed.h"
#include "Utils.h"
class Enemy
{

public:
    Enemy();
    void nuclearPlaneinit();
    void superSonicinit();
    void draw(N5110 &lcd);
    void update(bool enemyNuclearPlaneCollision, bool enemySupersonicCollision, bool enemySupersonicPlayerJetCollision);
    Position2D getNuclearPlane_pos();
    Position2D getSupersonic_pos();
    void setNuclearPlane_pos(Position2D p);
    void setSupersonic_pos(Position2D p);
private:

    Position2D p;
    int _size;
    int _xnuclearPlane;
    int _ynuclearPlane;
    int _xsupersonic;
    int _ysupersonic;
    int _speednuclearPlane;
    int _speedSupersonic;
    bool enemyNuclearPlaneCollision;
    bool enemySuperSonicCollision;
    bool enemySupersonicPlayerJetCollision;
    const int _nuclearPlane[14][15] =   {{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0}
                                        ,{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
                                        ,{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
                                        ,{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
                                        ,{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0}
                                        ,{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0}
                                        ,{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0}
                                        ,{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0}
                                        ,{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                                        ,{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                                        ,{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0}
                                        ,{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0}
                                        ,{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
                                        ,{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0}};
    
    const int _supersonic[10][9] =  {{0,0,1,1,1,1,1,0,0},
                                     {0,1,1,1,1,1,1,1,0},
                                     {1,1,1,0,0,0,1,1,1},
                                     {0,1,1,1,0,1,1,1,0},
                                     {0,0,1,1,1,1,1,0,0},
                                     {0,0,1,1,1,1,1,0,0},
                                     {0,0,0,1,1,1,0,0,0},
                                     {0,0,0,1,1,1,0,0,0},
                                     {0,0,0,0,1,0,0,0,0},
                                     {0,0,0,0,1,0,0,0,0}};
};
#endif




