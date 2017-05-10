#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using std::vector;
using sf::Sprite;
using sf::Texture;
using sf::Clock;
using sf::RenderWindow;

class Background {
public:
    Background(int windowHeight);
    void update();
    void draw(RenderWindow& window);
    void create(int windowHeight);
    void init(int windowHeight);
private:
    int _windowHeight;
    vector<Sprite> _backgrounds;
    vector<Sprite>::iterator _backgroundItr;
    Texture _backgroundTexture;
    Clock _backgroundMovementClock;
    
    void loadBackgroundTexture();
    void loadBackgroundSprites();
};

#endif
