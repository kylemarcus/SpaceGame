#include "Explosion.hpp"

Explosion::Explosion(int x, int y) {
    createExplosionSprite();
    loadExplosionTexture(x, y);
}

void Explosion::createExplosionSprite() {
    _explosionTexture.loadFromFile(resourcePath() + "explosion.png");
}

void Explosion::loadExplosionTexture(int x, int y) {
    _explosionSprite.setPosition(x-15, y-15);  // 15 is offset based on a 32x32 image.
    _explosionSprite.setTexture(_explosionTexture);
    _explosionTextureIndexX = _explosionTextureIndexY = 0;
    _explosionSprite.setTextureRect(sf::IntRect(0, 0, TEXTURE_SIZE, TEXTURE_SIZE));
}

void Explosion::update() {
    if (_explosionClock.getElapsedTime().asMicroseconds() > 250 && !_animationOver) {
        
        int x = _explosionTextureIndexX++ * TEXTURE_SIZE;
        int y = _explosionTextureIndexY * TEXTURE_SIZE;
        _explosionSprite.setTextureRect(sf::IntRect(x, y, TEXTURE_SIZE, TEXTURE_SIZE));
        
        if (_explosionTextureIndexX == MAX_TEXTURE_INDEX && _explosionTextureIndexY == MAX_TEXTURE_INDEX) {
            _animationOver = true;
        } else if (_explosionTextureIndexX == MAX_TEXTURE_INDEX) {
            _explosionTextureIndexX = 0;
            _explosionTextureIndexY++;
        }
        
        _explosionClock.restart();
    }
}

void Explosion::draw(RenderWindow &window) {
    window.draw(_explosionSprite);
}

bool Explosion::shouldDelete() {
    return _animationOver;
}
