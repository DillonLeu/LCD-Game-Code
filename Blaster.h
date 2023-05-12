#ifndef BLASTER
#define BLASTER

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

class Blaster 
{
    public:
        Blaster();
        void draw(N5110 &lcd);
        void init();
        void update(bool nuclearPlaneCollision, bool supersonicCollision);
        Position2D get_pos();
        void set_pos(Position2D p);

    private:
        Position2D p;
        bool collision;
        int _x;
        int _y;
        int _speed;
        int _firingSpeed;
        const int _blaster[3][1] = {{1}
                                   ,{1}
                                   ,{1}};
    
};




#endif
