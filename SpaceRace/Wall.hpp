#ifndef Wall_hpp
#define Wall_hpp

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>     /* cout */
#include <deque>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using std::deque;
using std::cout;
using std::endl;
using sf::Sprite;
using sf::Texture;
using sf::Clock;
using sf::RenderWindow;
using sf::FloatRect;

class Wall {
public:
    enum WallPos {left, right};
    
    Wall(int windowWidth, int windowHeight, WallPos wallPos);
    void update();
    void draw(RenderWindow& window);
    bool collidesWith(const FloatRect& rec);
    
private:
    enum Movement { up, down };
    const int WALL_ROW_HEIGHT = 32;
    const int WALL_TILE_WIDTH = 32;
    const float WALL_MOVE_SPEED = 0.005;
    int _windowHeight;
    int _windowWidth;
    WallPos _wallPos;
    deque<Sprite *> _wallRowsQueue;
    Texture _wallTexture;
    Movement _wallMovement;
    Clock _wallMovementClock;
    int _wallRowWidthCount;
    int _prevWallWidth;
    
    void loadWallTexture();
    void initWallCreation();
    Sprite * createWallRow(int x, int y);
    int getRandBetween(int min, int max);
    int getRandWallWidth();
    int getRandRowWidthCount();
    void moveWallUp();
    void moveWallDown();
    void moveAllWallRowsDown();
    void addNewWallRowToTopIfNeeded();
    void deleteHiddenBottomWallRows();
};

#endif
