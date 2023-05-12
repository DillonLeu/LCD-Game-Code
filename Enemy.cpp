#include "Enemy.h" 
#include <stdlib.h>
Enemy::Enemy(){}

void Enemy::nuclearPlaneinit(){
    srand(time(0));
    _xnuclearPlane = (rand() % 68);
    _ynuclearPlane = -(10 + (rand() % 20));
    _speednuclearPlane = (1 + (rand() % 3));
}

void Enemy::superSonicinit(){
    srand(time(0));
    _xsupersonic = (1 + (rand() % 73));
    _ysupersonic = -(10 + rand() % 15);
    _speedSupersonic = (3 + (rand() % 5));
}

void Enemy::draw(N5110 &lcd){
    lcd.drawSprite(_xnuclearPlane, _ynuclearPlane, 14, 15, (int*) _nuclearPlane);
    lcd.drawSprite(_xsupersonic, _ysupersonic, 10, 9, (int*) _supersonic);
}

void Enemy::update(bool enemyNuclearPlaneCollision, bool enemySupersonicCollision, bool enemySupersonicPlayerJetCollision)
{
    if (enemyNuclearPlaneCollision == false)
    {
    _ynuclearPlane += _speednuclearPlane;
    }
    else if (enemyNuclearPlaneCollision == true)
    {
    _speednuclearPlane = 0;
    }
    if (enemySupersonicCollision == false && enemySupersonicPlayerJetCollision == false)
    {
    _ysupersonic += _speedSupersonic;
    }
    else if (enemySupersonicCollision == true || enemySupersonicPlayerJetCollision == true)
    {
    _speedSupersonic = 0;
    }
}

Position2D Enemy::getNuclearPlane_pos()
{
    return {_xnuclearPlane, _ynuclearPlane};
}

Position2D Enemy::getSupersonic_pos()
{
    return {_xsupersonic, _ysupersonic};
}

void Enemy::setNuclearPlane_pos(Position2D p)
{
    _xnuclearPlane = p.x;
    _ynuclearPlane = p.y;

}

void Enemy::setSupersonic_pos(Position2D p)
{
    _xsupersonic = p.x;
    _ysupersonic = p.y;

}
