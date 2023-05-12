#ifndef INVASIONENGINE
#define INVASIONENGINE

#include "Utils.h"
#include "PlayerJet.h"
#include "Blaster.h"
#include "Enemy.h"
#include "ExplosionEffect.h"
#include "Scoreboard.h"
#include "mbed.h"
#include <tuple>

class InvasionEngine{
    
    public:
    InvasionEngine();
    void init();
    tuple<int,int> update(UserInput input);
    void lcdBoundary();
    void draw(N5110 &lcd);
    void TriggeredButton();
    void reloadBlaster();
    void checkBlasterEnemyCollision();
    void respawnEnemy();
    void checkPlayerEnemyCollision();
    private:
    Position2D playerJet_pos;
    Position2D blaster_pos;
    Position2D enemyBlaster_pos;
    Position2D enemyNuclearPlane_pos;
    Position2D enemySupersonic_pos;
    PlayerJet _playerJet;
    Blaster _blaster;
    Enemy _enemy;
    UserInput input;
    ExplosionEffect _explode;
    Scoreboard _score;
    bool _blasterNuclearPlaneCollision;
    bool _blasterSupersonicCollision;
    bool _enemySupersonicPlayerJetCollision;
    bool _enemySupersonicCollision;
    int _updateExplosionScreenForBlasterNuclearPlaneCollision;
    int _updateExplosionScreenForBlasterSupersonicCollision;
    int _updateGameOverExplosionScreen;
    int _state;
    int _lives;
    int score;
    int _starTransition;



};
#endif
