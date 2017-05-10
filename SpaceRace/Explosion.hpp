#ifndef Explosion_hpp
#define Explosion_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using std::cout;
using std::endl;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::Clock;

class Explosion {
public:
    Explosion(int x, int y);
    void update();
    void draw(RenderWindow& window);
    bool shouldDelete();
private:
    Sprite _explosionSprite;
    Texture _explosionTexture;
    Clock _explosionClock;
    const int MAX_TEXTURE_INDEX = 4;
    const int TEXTURE_SIZE = 64;
    int _explosionTextureIndexY;
    int _explosionTextureIndexX;
    bool _animationOver = false;
    
    void createExplosionSprite();
    void loadExplosionTexture(int x, int y);
};

#endif
