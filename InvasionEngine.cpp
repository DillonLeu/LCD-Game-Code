#include "InvasionEngine.h"

DigitalIn _buttonA(PC_11);

InvasionEngine::InvasionEngine() {_lives = 3; };

void InvasionEngine::init() 
{
    _playerJet.init();
    _enemy.nuclearPlaneinit();
    _enemy.superSonicinit();
    _blaster.init();
    _explode.init();
    _score.init();
    _buttonA.mode(PullNone);
    _blasterNuclearPlaneCollision = false;
    _blasterSupersonicCollision = false;
    _enemySupersonicPlayerJetCollision = false;
    _updateExplosionScreenForBlasterNuclearPlaneCollision = 0;
    _updateExplosionScreenForBlasterSupersonicCollision = 0;
    _updateGameOverExplosionScreen = 0;
    _starTransition = 0;
    score = 0;
}

tuple<int,int> InvasionEngine::update(UserInput input)
{
    _playerJet.update(input, _enemySupersonicPlayerJetCollision);
    // printf("Enemy Jet Collision = %s", _blasterNuclearPlaneCollision ? "true":"false");
    _enemy.update(_blasterNuclearPlaneCollision,_blasterSupersonicCollision,_enemySupersonicPlayerJetCollision);
    enemyNuclearPlane_pos = _enemy.getNuclearPlane_pos();
    enemySupersonic_pos = _enemy.getSupersonic_pos();
    blaster_pos = _blaster.get_pos();
    playerJet_pos = _playerJet.get_pos();
    checkPlayerEnemyCollision();
    if (_buttonA == 0) 
    {
        TriggeredButton();
    }
    if (_state == 1)
    {
        //printf("Draw Blaster");
        checkBlasterEnemyCollision();
        _blaster.update(_blasterNuclearPlaneCollision, _blasterSupersonicCollision);
        respawnEnemy();
    }
    else 
    {
        _blaster.set_pos(playerJet_pos);
    }
    if (enemyNuclearPlane_pos.y >= 50)
        {
        _enemy.nuclearPlaneinit();
        _lives -= 1;
        }
    if (enemySupersonic_pos.y >= 48)
    {
        _enemy.superSonicinit();
    }
    if (_blasterNuclearPlaneCollision == true || _blasterSupersonicCollision == true)
    {
        _blaster.set_pos(playerJet_pos);
    }
    reloadBlaster(); 
    return {_lives, score};
}

void InvasionEngine::draw(N5110 &lcd)
{
    _starTransition += 1;
    if(_starTransition == 1)
    {
    lcd.setPixel(5,5, true);
    lcd.setPixel(5,15, true);
    lcd.setPixel(5,25, true);
    lcd.setPixel(5,35, true);

    lcd.setPixel(25,5, true);
    lcd.setPixel(25,15, true);
    lcd.setPixel(25,25, true);
    lcd.setPixel(25,35, true);

    lcd.setPixel(45,15, true);
    lcd.setPixel(45,25, true);
    lcd.setPixel(45,35, true);
    lcd.setPixel(45,45, true);

    lcd.setPixel(65,5, true);
    lcd.setPixel(65,15, true);
    lcd.setPixel(65,25, true);
    lcd.setPixel(65,35, true);
    }
    else if (_starTransition == 2)
    {
    lcd.setPixel(15,10, true);
    lcd.setPixel(15,20, true);
    lcd.setPixel(15,30, true);
    lcd.setPixel(15,40, true);

    lcd.setPixel(35,10, true);
    lcd.setPixel(35,20, true);
    lcd.setPixel(35,30, true);
    lcd.setPixel(35,40, true);
   
    lcd.setPixel(55,10, true);
    lcd.setPixel(55,20, true);
    lcd.setPixel(55,30, true);
    lcd.setPixel(55,40, true);

    lcd.setPixel(75,10, true);
    lcd.setPixel(75,20, true);
    lcd.setPixel(75,30, true);
    lcd.setPixel(75,40, true);
    _starTransition = 0;
    }

    _playerJet.draw(lcd);
    _enemy.draw(lcd);
    _blaster.draw(lcd);
    _explode.drawPlayerJetExplosion(lcd);
    _explode.drawSuperSonicExplosion(lcd);
    _explode.drawExplosion(lcd);
    _score.draw(lcd);

    lcd.drawLine(0,47,83,47,1);
    lcd.drawLine(0,0,0,47,1);
    lcd.drawLine(83,0,83,47,1);

    
}


void InvasionEngine::reloadBlaster()
{
    if ((blaster_pos.y <= -10) && ((_blasterNuclearPlaneCollision == false) && (_blasterSupersonicCollision == false)))
    {
        _blaster.set_pos(playerJet_pos);
        //printf("playerJet_pos = %d", playerJet_pos.x);
        _state = 0;
    }   
}

void InvasionEngine::TriggeredButton()
{
    _state = 1;
}

void InvasionEngine::checkBlasterEnemyCollision()
{
    if (
       (((blaster_pos.y <= enemyNuclearPlane_pos.y + 14) && (blaster_pos.y >= enemyNuclearPlane_pos.y)) && ((blaster_pos.x >= enemyNuclearPlane_pos.x + 4) && (blaster_pos.x <= enemyNuclearPlane_pos.x + 10)))
       || ((blaster_pos.y <= enemyNuclearPlane_pos.y + 10) && (blaster_pos.y >= enemyNuclearPlane_pos.y + 7) && (((blaster_pos.x >= enemyNuclearPlane_pos.x) && (blaster_pos.x <= enemyNuclearPlane_pos.x + 4)) || ((blaster_pos.x >= enemyNuclearPlane_pos.x + 10) && (blaster_pos.x <= enemyNuclearPlane_pos.x + 14))))
       ) 
    {
        // printf("enemyJet x = %d, y = %d\n", enemyNuclearPlane_pos.x, enemyNuclearPlane_pos.y);
        // printf("blaster y = %d\n", blaster_pos.y);
        _blasterNuclearPlaneCollision = true;
    }
    if (_blasterNuclearPlaneCollision == true)
    {
        _updateExplosionScreenForBlasterNuclearPlaneCollision += 1;
        _explode.updateBlasterNuclearPlaneExplosionEffect(enemyNuclearPlane_pos, _updateExplosionScreenForBlasterNuclearPlaneCollision);
    }

    if (
       (((blaster_pos.y <= enemySupersonic_pos.y + 10) && (blaster_pos.y >= enemySupersonic_pos.y)) && ((blaster_pos.x >= enemySupersonic_pos.x + 3) && (blaster_pos.x <= enemySupersonic_pos.x + 7)))
       || ((blaster_pos.y <= enemySupersonic_pos.y + 3) && ((blaster_pos.x >= enemySupersonic_pos.x) && (blaster_pos.x <= enemySupersonic_pos.x + 9)))
       )
    {
        _blasterSupersonicCollision = true;
    }
    if (_blasterSupersonicCollision == true)
    {
        _updateExplosionScreenForBlasterSupersonicCollision += 1;
        _explode.updateBlasterSupersonicExplosionEffect(enemySupersonic_pos, _updateExplosionScreenForBlasterSupersonicCollision);
    }

} 

//respawn enemy jet when it got destroyed and after explosion effect ends
void InvasionEngine::respawnEnemy()
{
    if (_updateExplosionScreenForBlasterNuclearPlaneCollision == 5 && _blasterNuclearPlaneCollision == true)
    {
        _enemy.nuclearPlaneinit();
        _explode.init();
        _state = 0;
        score = _score.update();
        _blaster.set_pos(playerJet_pos);
        _updateExplosionScreenForBlasterNuclearPlaneCollision = 0;
        _blasterNuclearPlaneCollision = false;
    }
    if (_updateExplosionScreenForBlasterSupersonicCollision == 5 && _blasterSupersonicCollision == true)
    {
        _enemy.superSonicinit();
        _explode.init();
        _state = 0;
        score = _score.update();
        _blaster.set_pos(playerJet_pos);
        _updateExplosionScreenForBlasterSupersonicCollision = 0;
        _blasterSupersonicCollision = false;

    }


}


void InvasionEngine::checkPlayerEnemyCollision()
{
    if (
       ((playerJet_pos.y <= enemySupersonic_pos.y + 10) && ((playerJet_pos.x + 4 >= enemySupersonic_pos.x + 4) && (playerJet_pos.x + 4 <= enemySupersonic_pos.x + 10)))
       || ((playerJet_pos.y + 7 <= enemySupersonic_pos.y + 11) && (((playerJet_pos.x + 11 >= enemySupersonic_pos.x) && (playerJet_pos.x + 11 <= enemySupersonic_pos.x + 4)) || ((playerJet_pos.x <= enemySupersonic_pos.x + 6) && (playerJet_pos.x >= enemySupersonic_pos.x + 10))))
       || (_enemySupersonicPlayerJetCollision == true)
    )
    {
        _enemySupersonicPlayerJetCollision = true;
        _updateGameOverExplosionScreen += 1;
        // _enemy.update(_blasterNuclearPlaneCollision, _blasterSupersonicCollision,);
        _playerJet.update(input, _enemySupersonicPlayerJetCollision);
        _explode.updateGameOverPlayerJet(playerJet_pos, _updateGameOverExplosionScreen);
        _explode.updateGameOverSuperSonic(enemySupersonic_pos, _updateGameOverExplosionScreen);

    }
    if (_updateGameOverExplosionScreen == 13)
    {
        _lives = 0;
    }
}
