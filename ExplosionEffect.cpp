#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect() {};


void ExplosionEffect::init() 
{
    _x = -20;
    _y = -20;
    _xSupersonic = 0;
    _ySupersonic = 0;
    _xPlayerJet = 0;
    _yPlayerJet = 0;
}


void ExplosionEffect::drawSuperSonicExplosion(N5110 &lcd)
{
    if (_updateGameOverSuperSonic == 1)
    {
    lcd.drawSprite(_xSupersonic + 5, _ySupersonic + 7, 3, 4, (int*) explosionEffect0);
    }
    else if (_updateGameOverSuperSonic == 2)
    {
    lcd.drawSprite(_xSupersonic + 4, _ySupersonic + 6, 6, 7, (int*) explosionEffect1);
    }
    else if (_updateGameOverSuperSonic == 3)
    {
    lcd.drawSprite(_xSupersonic + 3, _ySupersonic + 5, 8, 10, (int*) explosionEffect2);
    }
    else if (_updateGameOverSuperSonic == 4)
    {
    lcd.drawSprite(_xSupersonic + 2, _ySupersonic + 3, 11, 13, (int*) explosionEffect3);
    }
    else if (_updateGameOverSuperSonic == 5)
    {
    lcd.drawSprite(_xSupersonic + 1, _ySupersonic + 1, 15, 15, (int*) explosionEffect4);
    }
    else if (_updateGameOverSuperSonic == 6)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect5);
    }
    else if (_updateGameOverSuperSonic == 7)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect6);
    }
    else if (_updateGameOverSuperSonic == 8)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect7);
    }
    else if (_updateGameOverSuperSonic == 9)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect8);
    }
    else if (_updateGameOverSuperSonic == 10)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect9);
    }
    else if (_updateGameOverSuperSonic == 11)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect10);
    }
    else if (_updateGameOverSuperSonic == 12)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect11);
    }
    else if (_updateGameOverSuperSonic == 13)
    {
    lcd.drawSprite(_xSupersonic, _ySupersonic, 17, 17, (int*) explosionEffect12);
    }
}

void ExplosionEffect::drawPlayerJetExplosion(N5110 &lcd)
{
    if (_updateGameOverPlayerJet == 1)
    {
    lcd.drawSprite(_xPlayerJet + 5, _yPlayerJet + 7, 3, 4, (int*) explosionEffect0);
    }
    else if (_updateGameOverPlayerJet == 2)
    {
    lcd.drawSprite(_xPlayerJet + 4, _yPlayerJet + 6, 6, 7, (int*) explosionEffect1);
    }
    else if (_updateGameOverPlayerJet == 3)
    {
    lcd.drawSprite(_xPlayerJet + 3, _yPlayerJet + 5, 8, 10, (int*) explosionEffect2);
    }
    else if (_updateGameOverPlayerJet == 4)
    {
    lcd.drawSprite(_xPlayerJet + 2, _yPlayerJet + 3, 11, 13, (int*) explosionEffect3);
    }
    else if (_updateGameOverPlayerJet == 5)
    {
    lcd.drawSprite(_xPlayerJet + 1, _yPlayerJet + 1, 15, 15, (int*) explosionEffect4);
    }
    else if (_updateGameOverPlayerJet == 6)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect5);
    }
    else if (_updateGameOverPlayerJet == 7)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect6);
    }
    else if (_updateGameOverPlayerJet == 8)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect7);
    }
    else if (_updateGameOverPlayerJet == 9)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect8);
    }
    else if (_updateGameOverPlayerJet == 10)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect9);
    }
    else if (_updateGameOverPlayerJet == 11)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect10);
    }
    else if (_updateGameOverPlayerJet == 12)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect11);
    }
    else if (_updateGameOverPlayerJet == 13)
    {
    lcd.drawSprite(_xPlayerJet, _yPlayerJet, 17, 17, (int*) explosionEffect12);
    }
}

void ExplosionEffect::drawExplosion(N5110 &lcd)
{
    if (_updateExplosionScreen == 1)
    {
    lcd.drawSprite(_x + 5, _y + 7, 3, 4, (int*) explosionEffect0);
    }

    else if (_updateExplosionScreen == 2)
    {
    lcd.drawSprite(_x + 3, _y + 5, 8, 10, (int*) explosionEffect2);
    }
    else if (_updateExplosionScreen == 3)
    {
    lcd.drawSprite(_x, _y, 17, 17, (int*) explosionEffect10);
    }
    else if (_updateExplosionScreen == 4)
    {
    lcd.drawSprite(_x, _y, 17, 17, (int*) explosionEffect12);
    }

}


void ExplosionEffect::updateBlasterSupersonicExplosionEffect(Position2D p, int _updateScreen0)
{
    _updateExplosionScreen = _updateScreen0;
    _x = p.x;
    _y = p.y;
}

void ExplosionEffect::updateBlasterNuclearPlaneExplosionEffect(Position2D p, int _updateScreen1)
{
    _updateExplosionScreen = _updateScreen1;
    _x = p.x;
    _y = p.y;
}

void ExplosionEffect::updateGameOverPlayerJet(Position2D p, int _updateScreen2)
{
    _updateGameOverPlayerJet = _updateScreen2;
    _xPlayerJet = p.x;
    _yPlayerJet = p.y;
}

void ExplosionEffect::updateGameOverSuperSonic(Position2D p, int _updateScreen3)
{
    _updateGameOverSuperSonic = _updateScreen3;
    _xSupersonic = p.x;
    _ySupersonic = p.y;
}
