#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Wall.hpp"
#include "Laser.hpp"

using std::vector;
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::Clock;

class Player {
public:
    Player(int windowWidth, int windowHeight);
    void update();
    void draw(RenderWindow& window);
    bool checkIfWallHit(Wall& wall);
    void checkIfLaserHitWall(Wall& wall);
    void reset();
    vector<Laser *>& getLasers();
    void deleteLaser(Laser * laser);
private:
    const int PLAYER_SPRITE_WIDTH = 25;
    const int PLAYER_SPRITE_HEIGHT = 30;
    const int PLAYER_MAX_SPRITE_INDEX = 5;
    int _windowHeight;
    int _windowWidth;
    Texture _playerTexture;
    Sprite _playerSprite;
    int _playerSpeed;
    Clock _playerSpriteChangeClock;
    int _playerSpriteIndex;
    vector<Laser *> _lasers;
    Clock _laserClock;
    
    void loadPlayerTexture();
    void loadPlayerSprite();
    int x();
    int y();
    void changePlayerSprite();
};

#endif
