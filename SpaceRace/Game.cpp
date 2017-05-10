#include "Game.hpp"

Game::Game() :
_background(WINDOW_HEIGHT),
_leftWall(WINDOW_WIDTH, WINDOW_HEIGHT, Wall::WallPos::left),
_rightWall(WINDOW_WIDTH, WINDOW_HEIGHT, Wall::WallPos::right),
_player(WINDOW_WIDTH, WINDOW_HEIGHT) {
    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Race");
}

void Game::createWindow(int width, int height, string title) {
    _window.create(VideoMode(width, height), title);
    _window.setFramerateLimit(FRAME_RATE);
}

void Game::loop() {
    
    // Start the game loop
    while (_window.isOpen())
    {
        handleWindowClose();
  
        // Clear screen
        _window.clear();
        
        updateGame();
        
        // Update the window
        _window.display();
    }
    
}

void Game::handleWindowClose() {
    // Process events
    sf::Event event;
    while (_window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _window.close();
        }
    }
}

void Game::updateGame() {
    _background.update();
    _background.draw(_window);
    
    _leftWall.update();
    _leftWall.draw(_window);
    
    _rightWall.update();
    _rightWall.draw(_window);
    
    _player.update();
    
    if (_player.checkIfWallHit(_leftWall) || _player.checkIfWallHit(_rightWall)) {
        _player.reset();
    }
    _player.checkIfLaserHitWall(_leftWall);
    _player.checkIfLaserHitWall(_rightWall);
    
    static vector<Explosion *>::iterator explosion;
    for (explosion = _explosions.begin(); explosion != _explosions.end(); explosion++) {
        (**explosion).update();
        (**explosion).draw(_window);
    }
    
    /* update and draw each enemy */
    static vector<Enemy *>::iterator enemy;
    for (enemy = _enemies.begin(); enemy != _enemies.end(); enemy++) {
        (**enemy).update();
        (**enemy).draw(_window);
    }
    
    /* spawn new enemies */
    if (_enemySpawnClock.getElapsedTime().asSeconds() > 4) {
        _enemies.push_back(new Enemy(WINDOW_WIDTH, WINDOW_HEIGHT));
        _enemySpawnClock.restart();
    }
    
    /* check if enemy was hit by a laser */
    for (enemy = _enemies.begin(); enemy != _enemies.end();) {
        Laser * laserHit = (**enemy).hitByLaser(_player.getLasers());
        if (laserHit) {
            // delete the laser
            _player.deleteLaser(laserHit);
            
            // create an explosion
            _explosions.push_back(new Explosion((**enemy).x(), (**enemy).y()));
            
            // delete the enemy
            enemy = _enemies.erase(enemy);
        } else {
            enemy++;
        }
    }
    
    /* delete any explosions that are finished */
    for (explosion = _explosions.begin(); explosion != _explosions.end();) {
        if ((**explosion).shouldDelete()) {
            explosion = _explosions.erase(explosion);
        } else {
            explosion++;
        }
    }
    
    _player.draw(_window);
}
