#include "Background.hpp"

Background::Background(int windowHeight) {
    init(windowHeight);
}

void Background::create(int windowHeight) {
    init(windowHeight);
}

void Background::init(int windowHeight) {
    _windowHeight = windowHeight;
    
    loadBackgroundTexture();
    loadBackgroundSprites();
}

void Background::loadBackgroundTexture() {
    _backgroundTexture.loadFromFile(resourcePath() + "starsBackground.jpg");
}

void Background::loadBackgroundSprites() {
    sf::Sprite background;
    
    background.setPosition(0, 0);
    background.setTexture(_backgroundTexture);
    _backgrounds.push_back(background);
    
    background.setPosition(0, - _windowHeight);
    _backgrounds.push_back(background);
}

void Background::update() {
    if (_backgroundMovementClock.getElapsedTime().asMicroseconds() > 1) {
        for(_backgroundItr = _backgrounds.begin(); _backgroundItr != _backgrounds.end(); _backgroundItr++) {
            (*_backgroundItr).setPosition(0, (*_backgroundItr).getPosition().y + 1);
            
            if ((*_backgroundItr).getPosition().y > _windowHeight) {
                (*_backgroundItr).setPosition(0, - _windowHeight);
            }
        }
        _backgroundMovementClock.restart();
    }
}

void Background::draw(sf::RenderWindow& window) {
    for(_backgroundItr = _backgrounds.begin(); _backgroundItr != _backgrounds.end(); _backgroundItr++) {
        window.draw(*_backgroundItr);
    }
}
