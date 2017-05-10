#ifndef Laser_hpp
#define Laser_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Wall.hpp"

using sf::RectangleShape;
using sf::RenderWindow;
using sf::Clock;
using sf::FloatRect;

class Laser {
public:
    Laser(int x, int y, int speed);
    void update();
    void draw(RenderWindow& window);
    bool outOfView(int windowHeight);
    bool hitWall(Wall& wall);
    FloatRect getBounds();
private:
    RectangleShape _laserRec;
    int _laserSpeed;
    int _laserWidth;
    int _laserHeight;
    int _laserClockSpeed;
    Clock _laserUpdateClock;
    int x();
    int y();
};

#endif
