#include "Gameover.h"

void Gameover::init()
{
    _x = 23;
    _y = 36;
    _p.x = -14;
    _p.y = 0;
    _nuclearBomb_Pos.x = 38;
    _nuclearBomb_Pos.y = 6;
}

int Gameover::draw(N5110 &lcd, int _explosionEffect, int score)
{
    lcd.clear();
    lcd.drawSprite(62,38,9,20,(int*) mountain1);
    lcd.drawSprite(0,38,9,20,(int*) mountain);
    lcd.drawSprite(23,36,13,38,(int*) cityDestroy);
    lcd.drawSprite(_p.x,_p.y,6,14,(int*) enemyJet);
    lcd.drawLine(0, 47, 84, 47, FILL_BLACK);
    
    if (_p.x >= 34)
    {
        lcd.drawSprite(_nuclearBomb_Pos.x,_nuclearBomb_Pos.y,7,7,(int*) nuclearBomb);
    }
    if (_nuclearBomb_Pos.y == 40){
        if (_explosionEffect == 0){
            lcd.drawSprite(_x + 16,_y + 9,2,4,(int*) nuclearExplosion0);
        }
        else if (_explosionEffect == 1){
        lcd.drawSprite(_x + 14,_y + 8,3,8,(int*) nuclearExplosion1);
        }
        else if (_explosionEffect == 2){
        lcd.drawSprite(_x + 12,_y + 7,4,12,(int*) nuclearExplosion2);
        }
        else if (_explosionEffect == 3){
        lcd.drawSprite(_x + 10,_y + 6,5,16,(int*) nuclearExplosion3);
        }
        else if (_explosionEffect == 4){
        lcd.drawSprite(_x + 8,_y + 5,6,20,(int*) nuclearExplosion4);
        }
        else if (_explosionEffect == 5){
        lcd.drawSprite(_x + 6,_y + 4,7,24,(int*) nuclearExplosion5);
        }
        else if (_explosionEffect == 6){
        lcd.drawSprite(_x + 4,_y + 3,8,28,(int*) nuclearExplosion6);
        }
        else if (_explosionEffect == 7){
        lcd.drawSprite(_x + 2,_y + 2,9,32,(int*) nuclearExplosion7);
        }
        else if (_explosionEffect == 8){
        lcd.drawSprite(_x + 0,_y + 1,9,35,(int*) nuclearExplosion8);
        }
        else if (_explosionEffect == 9){
        lcd.drawSprite(_x - 2, _y,10,39,(int*) nuclearExplosion9);
        }
        else if (_explosionEffect == 10){
        lcd.drawSprite(_x, _y,10,39,(int*) nuclearExplosion10);
        }
        else if (_explosionEffect == 11){
        lcd.drawSprite(_x, _y,10,39,(int*) nuclearExplosion11);
        }
        else if (_explosionEffect == 12){
        lcd.drawSprite(_x, _y,10,39,(int*) nuclearExplosion12);
        }
        else if (_explosionEffect == 13){
        lcd.drawSprite(_x, _y,10,39,(int*) nuclearExplosion13);
        }
        else if (_explosionEffect == 14){
        lcd.drawSprite(_x, _y,10,39,(int*) nuclearExplosion14);
        lcd.printString("   GAMEOVER   ", 0, 1);
        lcd.printString("MISSION FAILED", 0, 2);
        sprintf(buffer, "  SCORE : %d  ", score);
        lcd.printString(buffer, 0, 3);
        }
        
        _explosionEffect += 1;
    }
    thread_sleep_for(100);
    lcd.refresh();
    if (_explosionEffect == 14)
    {
        return _explosionEffect;
    }
    return _explosionEffect;
}

void Gameover::updateEnemyJet()
{
    _p.x += 2;
    _p.y = 0;
    if (_p.x >= 84){
        _p.x = 84;
    }
}

void Gameover::updateNuclearBomb()
{
    if (_p.x > 34)
    {
    _nuclearBomb_Pos.x = 38;
    _nuclearBomb_Pos.y += 3;
    }
    if (_nuclearBomb_Pos.y >= 40){
        _nuclearBomb_Pos.y = 40;
    }
}
