#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Laser.hpp"

using std::vector;
using sf::Sprite;
using sf::Texture;
using sf::Clock;
using sf::RenderWindow;

class Enemy {
public:
    Enemy(int windowWidth, int windowHeight);
    void update();
    void draw(RenderWindow& window);
    Laser * hitByLaser(vector<Laser *>& lasers);
    int x();
    int y();
    
private:
    const int ENEMY_SPRITE_WIDTH = 32;
    const int ENEMY_SPRITE_HEIGHT = 28;
    const int ENEMY_MAX_SPRITE_INDEX = 4;
    int _windowHeight;
    int _minWidth;
    int _maxWidth;
    Sprite _enemySprite;
    Texture _enemyTexture;
    int _enemySpeed;
    Clock _enemySpriteChangeClock;
    int _enemySpriteIndex;
    Clock _enemyMoveDownClock;
    Clock _enemyMoveSideClock;
    int _moveLeftSteps;
    int _moveRightSteps;
    
    void loadEnemyTexture();
    void loadEnemySprite();
    void changeEnemySprite();
    void moveEnemy();
    int getRandBetween(int min, int max);
};

#endif
