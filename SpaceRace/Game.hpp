#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Explosion.hpp"

using std::string;
using std::vector;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Clock;

class Game {
public:
    Game();
    void loop();
private:
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int FRAME_RATE = 60;
    RenderWindow _window;
    
    /* game players */
    Background _background;
    Wall _leftWall;
    Wall _rightWall;
    Player _player;
    vector<Enemy *> _enemies;
    Clock _enemySpawnClock;
    vector<Explosion *> _explosions;
    
    void createWindow(int width, int height, string title);
    void handleWindowClose();
    void updateGame();
};

#endif
