#include "Enemy.hpp"

Enemy::Enemy(int windowWidth, int windowHeight) {
    // this needs to be handled better. Wall tile is 32x32.
    // only can have a max of 4 tiles wide on each wall.
    // keep enimies inside this bounds.
    _minWidth = 5 * 32;
    _maxWidth = windowWidth - _minWidth;
    _windowHeight = windowHeight;
    
    loadEnemyTexture();
    loadEnemySprite();
}

void Enemy::loadEnemyTexture() {
    _enemyTexture.loadFromFile(resourcePath() + "EnemyShipSpriteSheet.png");
}

void Enemy::loadEnemySprite() {
    _enemySprite.setPosition(getRandBetween(_minWidth + 64, _maxWidth - 64), -ENEMY_SPRITE_HEIGHT);
    _enemySprite.setTexture(_enemyTexture);
    _enemySprite.setTextureRect(sf::IntRect(0, 0, ENEMY_SPRITE_WIDTH, ENEMY_SPRITE_HEIGHT));
    
    _enemySpeed = 3;
    _enemySpriteIndex = 1;
    
    srand (time(NULL));
    _moveLeftSteps = _moveRightSteps = 0;
    if (rand() % 2) {
        _moveLeftSteps = getRandBetween(2, 10);
    } else {
        _moveRightSteps = getRandBetween(2, 10);
    }
    
}

int Enemy::getRandBetween(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void Enemy::update() {
    changeEnemySprite();
    moveEnemy();
}

void Enemy::moveEnemy() {
    // move the enemy down
    if (_enemyMoveDownClock.getElapsedTime().asMilliseconds() > 100) {
        _enemySprite.setPosition(x(), y() + _enemySpeed);
        _enemyMoveDownClock.restart();
    }
    
    // move the enemy to the side
    if (_enemyMoveSideClock.getElapsedTime().asMilliseconds() > 50) {
        int xDelta = _moveLeftSteps > 0 ? - _enemySpeed : _enemySpeed;
        _enemySprite.setPosition(x() + xDelta, y());
        
        if (_moveLeftSteps > 0) {
            _moveLeftSteps--;
        } else {
            _moveRightSteps--;
        }
        
        if ( _moveLeftSteps < 0 || _moveRightSteps < 0) {
            _moveLeftSteps = _moveRightSteps = 0;
            if (rand() % 2) {
                _moveLeftSteps = getRandBetween(10, 20);
            } else {
                _moveRightSteps = getRandBetween(10, 20);
            }
        }
        
        if (x() < _minWidth) {
            _enemySprite.setPosition(_minWidth, y());
            _moveLeftSteps = 0;
            _moveRightSteps = getRandBetween(15, 20);
        }
        
        if (x() + ENEMY_SPRITE_WIDTH > _maxWidth) {
            _enemySprite.setPosition(_maxWidth - ENEMY_SPRITE_WIDTH, y());
            _moveRightSteps = 0;
            _moveLeftSteps = getRandBetween(15, 20);
        }
        
        _enemyMoveSideClock.restart();
    }
}

int Enemy::x() {
    return _enemySprite.getPosition().x;
}

int Enemy::y() {
    return _enemySprite.getPosition().y;
}

/* Returns the Laser pointer if it hits the enemy
 * else it return null if enemy is not hit */
Laser * Enemy::hitByLaser(vector<Laser *>& lasers) {
    vector<Laser *>::iterator laser;
    for (laser = lasers.begin(); laser != lasers.end(); laser++) {
        if (_enemySprite.getGlobalBounds().intersects((**laser).getBounds())) {
            return *laser;
        }
    }
    return NULL;
}

void Enemy::changeEnemySprite() {
    if (_enemySpriteChangeClock.getElapsedTime().asMilliseconds() > 300) {
        // change to different sprite in player space ship sprite sheet
        _enemySprite.setTextureRect(sf::IntRect(_enemySpriteIndex++ * ENEMY_SPRITE_WIDTH, 0, ENEMY_SPRITE_WIDTH, ENEMY_SPRITE_HEIGHT));
        
        // restart the clock
        _enemySpriteChangeClock.restart();
        
        // loop the player sprites
        if (_enemySpriteIndex == ENEMY_MAX_SPRITE_INDEX)
            _enemySpriteIndex = 0;
    }
}

void Enemy::draw(RenderWindow& window) {
    window.draw(_enemySprite);
}
