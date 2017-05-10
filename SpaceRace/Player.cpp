#include "Player.hpp"

Player::Player(int windowWidth, int windowHeight) {
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    
    loadPlayerTexture();
    loadPlayerSprite();
}

void Player::loadPlayerTexture() {
    _playerTexture.loadFromFile(resourcePath() + "PlayerSpaceShipSpriteSheet.png");
}

void Player::loadPlayerSprite() {
    _playerSprite.setPosition(400, 500);
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setTextureRect(sf::IntRect(0, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT));
    
    _playerSpeed = 3;
    _playerSpriteIndex = 1;
}

void Player::reset() {
    _playerSprite.setPosition(400, 500);
    _lasers.clear();
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _playerSprite.setPosition(x() - _playerSpeed, y());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _playerSprite.setPosition(x() + _playerSpeed, y());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _playerSprite.setPosition(x(), y() - _playerSpeed);
        if (y() < 0) {
            _playerSprite.setPosition(x(), 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _playerSprite.setPosition(x(), y() + _playerSpeed);
        if (y() > _windowHeight - PLAYER_SPRITE_HEIGHT) {
            _playerSprite.setPosition(x(), _windowHeight - PLAYER_SPRITE_HEIGHT);
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        //shoot off a laser
        if (_laserClock.getElapsedTime().asSeconds() > 1) {
            Laser * laser = new Laser(x() + PLAYER_SPRITE_WIDTH / 2, y() - 15, -10);
            _lasers.push_back(laser);
            _laserClock.restart();
        }
    }
    
    //update laser positions
    vector<Laser *>::iterator laser;
    for (laser = _lasers.begin(); laser != _lasers.end(); laser++) {
        (**laser).update();
    }
    
    //erase out of view lasers from memory
    for (laser = _lasers.begin(); laser != _lasers.end();) {
        if ((**laser).outOfView(_windowHeight))
            laser = _lasers.erase(laser);
        else
            laser++;
    }
    
    // change player sprite
    changePlayerSprite();
}

void Player::changePlayerSprite() {
    if (_playerSpriteChangeClock.getElapsedTime().asMilliseconds() > 150) {
        // change to different sprite in player space ship sprite sheet
        _playerSprite.setTextureRect(sf::IntRect(_playerSpriteIndex++ * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT));
        
        // restart the clock
        _playerSpriteChangeClock.restart();
        
        // loop the player sprites
        if (_playerSpriteIndex == PLAYER_MAX_SPRITE_INDEX)
            _playerSpriteIndex = 0;
    }
}

// TODO: this should probably be done in the game loop?
// game should handle what happens when a wall is hit.
// player should just know if it hit a wall or not.
bool Player::checkIfWallHit(Wall& wall) {
    return wall.collidesWith(_playerSprite.getGlobalBounds());
}

void Player::checkIfLaserHitWall(Wall& wall) {
    vector<Laser *>::iterator laser;
    for (laser = _lasers.begin(); laser != _lasers.end();) {
        if (wall.collidesWith((**laser).getBounds())) {
            laser = _lasers.erase(laser);
        } else {
            laser++;
        }
    }
    
    return false;
}
                                  
int Player::x() {
    return _playerSprite.getPosition().x;
}

int Player::y() {
    return _playerSprite.getPosition().y;
}

void Player::draw(RenderWindow& window) {
    window.draw(_playerSprite);
    
    vector<Laser *>::iterator laser;
    for (laser = _lasers.begin(); laser != _lasers.end(); laser++) {
        (**laser).draw(window);
    }
}

vector<Laser *>& Player::getLasers() {
    return _lasers;
}

void Player::deleteLaser(Laser * laser) {
    _lasers.erase(std::remove(_lasers.begin(), _lasers.end(), laser), _lasers.end());
}
