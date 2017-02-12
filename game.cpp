#include "game.h"
#include <SFML/System.hpp>

Game::Game()
    : gameWindow(sf::VideoMode(800,864),"Unnamed TD"), iGame(mManager, gameWindow),
    mManager("defaultmap1")
{
    iGame.load("ui.txt");
    gameWindow.setFramerateLimit(60);
}

void Game::start()
{
    double delta = 0;
    sf::Clock c;
    while(gameWindow.isOpen())
    {
        sf::Event e;
        while(gameWindow.pollEvent(e))
        {
            event_handler(e);
        }
        update(delta);
        render();
        delta = c.restart().asSeconds();
    }
}

void Game::event_handler(sf::Event e)
{
    if ( e.type == sf::Event::Closed )
        gameWindow.close();
    if ( !iGame.isDone() )
        iGame.event_handler(e);
}

void Game::update(double delta)
{
    if ( !iGame.isDone() )
        iGame.update(delta);
}

void Game::render()
{
    gameWindow.clear();
    gameWindow.draw(mManager.getCurrMap());
    if ( !iGame.isDone() )
        iGame.draw();
    gameWindow.display();
}
