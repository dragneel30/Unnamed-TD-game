#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MapManager.h"
#include "ingame.h"
class Game
{
    public:
        Game();
        void start();

    private:
        void event_handler(sf::Event e);
        void update(double delta);
        void render();

        sf::RenderWindow gameWindow;

        MapManager mManager;

        InGame iGame;
};

#endif // GAME_H
