#include "Wall.hpp"

Wall::Wall(int windowWidth, int windowHeight, WallPos wallPos) {
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _wallPos = wallPos;
    
    srand (time(NULL));
    
    loadWallTexture();
    initWallCreation();
}

void Wall::loadWallTexture() {
    _wallTexture.loadFromFile(resourcePath() + "wallTexture.png");
}

void Wall::initWallCreation() {
    
    int numWallRows = _windowHeight / WALL_ROW_HEIGHT + 1;
    
    _wallMovement = up;
    _prevWallWidth = 0;
    _wallRowWidthCount = getRandRowWidthCount();
    
    int x = (_wallPos == left) ? 0 : _windowWidth;
    _wallRowsQueue.push_back(createWallRow(x, 0));
}

Sprite * Wall::createWallRow(int x, int y) {
    Sprite * s = new Sprite();
    (*s).setPosition(x, y);
    (*s).setTexture(_wallTexture);
    (*s).setTextureRect(sf::IntRect(0, 0, getRandWallWidth(), WALL_ROW_HEIGHT));
    if (_wallPos == right) // flip sprite horizontly
        (*s).scale(-1.f, 1.f);
    return s;
}

int Wall::getRandWallWidth() {
    
    if (_wallMovement == up)
        moveWallUp();
    else
        moveWallDown();
    
    return _prevWallWidth;
}

void Wall::moveWallUp() {
    if (_wallRowWidthCount > 0) {
        _wallRowWidthCount--;
        _prevWallWidth += WALL_TILE_WIDTH;
    } else {
        _wallMovement = down;
        _prevWallWidth -= WALL_TILE_WIDTH;
    }
}

void Wall::moveWallDown() {
    if (_prevWallWidth > WALL_TILE_WIDTH) {  // alwasy keep at least 1 col
        _prevWallWidth -= WALL_TILE_WIDTH;
    } else {
        _wallMovement = up;
        _wallRowWidthCount = getRandRowWidthCount();
    }
}

int Wall::getRandRowWidthCount() {
    return getRandBetween(1, 4);
}

int Wall::getRandBetween(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void Wall::update() {
    if (_wallMovementClock.getElapsedTime().asMicroseconds() > WALL_MOVE_SPEED) {
        moveAllWallRowsDown();
        addNewWallRowToTopIfNeeded();
        deleteHiddenBottomWallRows();
        _wallMovementClock.restart();
    }
}

void Wall::moveAllWallRowsDown() {
    static deque<Sprite *>::iterator wallRow;
    for(wallRow = _wallRowsQueue.begin(); wallRow != _wallRowsQueue.end(); wallRow++) {
        int x = (_wallPos == left) ? 0 : _windowWidth;
        int y = (**wallRow).getPosition().y + 3;
        (**wallRow).setPosition(x, y);
    }
}

void Wall::addNewWallRowToTopIfNeeded() {
    Sprite * frontWallRow = _wallRowsQueue.front();
    if ((*frontWallRow).getPosition().y > 0) {
        int x = (_wallPos == left) ? 0 : _windowWidth;
        int y = (*frontWallRow).getPosition().y - WALL_ROW_HEIGHT;
        _wallRowsQueue.push_front(createWallRow(x, y));
    }
}

void Wall::deleteHiddenBottomWallRows() {
    // check if we need to delete the last row
    Sprite * lastWallRow = _wallRowsQueue.back();
    if ((*lastWallRow).getPosition().y > _windowHeight) {
        _wallRowsQueue.pop_back();
    }
}

void Wall::draw(RenderWindow& window) {
    static deque<Sprite *>::iterator wallRow;
    for(wallRow = _wallRowsQueue.begin(); wallRow != _wallRowsQueue.end(); wallRow++) {
        window.draw(**wallRow);
    }
}

bool Wall::collidesWith(const FloatRect &rec) {
    static deque<Sprite *>::iterator wallRow;
    for(wallRow = _wallRowsQueue.begin(); wallRow != _wallRowsQueue.end(); wallRow++) {
        if ((**wallRow).getGlobalBounds().intersects(rec)) {
            return true;
        }
    }
    return false;
}
