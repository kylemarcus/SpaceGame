#include "Laser.hpp"

Laser::Laser(int x, int y, int speed) {
    _laserWidth = 2;
    _laserHeight = 15;
    _laserClockSpeed = 50;
    _laserSpeed = speed;
    
    _laserRec.setSize(sf::Vector2f(_laserWidth, _laserHeight));
    _laserRec.setPosition(x, y);
    _laserRec.setFillColor(sf::Color::Red);
}

void Laser::update() {
    if (_laserUpdateClock.getElapsedTime().asMilliseconds() > _laserClockSpeed) {
        _laserRec.setPosition(x(), y() + _laserSpeed);
        _laserUpdateClock.restart();
    }
}

int Laser::x() {
    return _laserRec.getPosition().x;
}

int Laser::y() {
    return _laserRec.getPosition().y;
}

void Laser::draw(RenderWindow& window) {
    window.draw(_laserRec);
}

bool Laser::outOfView(int windowHeight) {
    return (y() + _laserHeight) < 0 || y() > windowHeight;
}

bool Laser::hitWall(Wall& wall) {
    return wall.collidesWith(_laserRec.getGlobalBounds());
}

FloatRect Laser::getBounds() {
    return _laserRec.getGlobalBounds();
}
