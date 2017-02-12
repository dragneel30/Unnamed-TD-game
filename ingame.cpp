#include "ingame.h"


void InGame::draw()
{
    gameWindow.draw(infoPlayerGold);
    gameWindow.draw(infoLife);
    gameWindow.draw(infoScore);
    if ( mouseHolding )
    gameWindow.draw(*mouseHolding);
    gameWindow.draw(wave.info);
    gameWindow.draw(currentInformation);
    for ( std::size_t a = 0; a < enemies.size(); a++ )
    {
        if ( enemies[a]->isAlive() )
            gameWindow.draw(*enemies[a]);
    }
    for ( std::size_t a = 0; a < towers.size(); a++ )
    {
        gameWindow.draw(towers[a]);
    }
    for ( int a = 0; a < boundaries.size(); a++ )
    {
        gameWindow.draw(boundaries[a]);
    }
    gameWindow.draw(shop);
}

void InGame::update(double delta)
{
    //mouseHolding->print();
    static Wave::waveInfo currWave = wave.getNextWave();
    if ( !currWave.hasFinishedSpawning() )
    {
        if ( timerForSpawn.getElapsedTime().asSeconds() >= currWave.timePerSpawn )
        {
            enemies.emplace_back(std::make_shared<Enemy>(currWave.enemy+".png",startingPos,currMap[0].position,boundaries[INFORMATION]));
            currWave.spawn();
            timerForSpawn.restart();
            timerForWave.restart();
        }
    }
    else
    {
        if ( timerForWave.getElapsedTime().asSeconds() >= wave.timePerWave )
        {
            currWave = wave.getNextWave();
        }
    }
    for ( int a = 0; a < enemies.size(); a++ )
    {
        if ( !enemies[a]->isAlive() )
        {
            playerGold += enemies[a]->bounty;
            score++;
            infoScore.setText("Score: " + dtostr(score));
            infoPlayerGold.setText("Gold: " + dtostr(playerGold));
            enemies.erase(enemies.begin()+a);

        }
    }
    for ( std::size_t a = 0; a < enemies.size(); a++ )
    {
        if ( enemies[a]->isAlive() )
        {
            if ( enemies[a]->hasReachedGoal() )
            {
                enemies[a]->incrementGoalIndex();
                if ( enemies[a]->getGoalIndexQuad() == leakPoint+4 )
                {
                    enemies.erase(enemies.begin()+a);
                }
                enemies[a]->setGoalPoint(currMap[enemies[a]->getGoalIndexQuad()].position);
            }
            enemies[a]->run(delta);
        }
    }
    for ( std::size_t a = 0; a < towers.size(); a++ )
    {
        towers[a].updateBullet(delta);
        if ( !enemies.empty() )
        {
            towers[a].findTarget(enemies);
            towers[a].changeRadiusColor(enemies);
        }
    }
}

Location InGame::getMouseLocation()
{
    sf::Vector2i mpos = sf::Mouse::getPosition(gameWindow);
    for ( int a = 0; a < boundaries.size(); a++ )
    {
        if ( boundaries[a].isMouseInside(mpos) )
        {
            return boundaries[a].loc;
        }
    }
    return NONE;
}

void InGame::syncTileToMouse(Entity& ent)
{
    sf::Vector2i pos = sf::Mouse::getPosition(gameWindow);
    pos.x = pos.x - ( pos.x % 32 );
    pos.y = pos.y - ( pos.y % 32 );
    ent.setPosition(sf::Vector2f(pos.x,pos.y));
}

void InGame::event_handler(sf::Event e)
{
    if ( e.type == sf::Event::MouseMoved )
    {
        if ( mouseHolding )
        {
            syncTileToMouse(*mouseHolding);
            syncTileToMouse(emptyTile);
        }
    }
    else if ( e.type == sf::Event::KeyPressed )
    {
        if ( e.key.code == sf::Keyboard::Space )
        {
            enemies.emplace_back(std::make_shared<Enemy>("bandit.png",startingPos,currMap[0].position,boundaries[INFORMATION]));
        }
    }
    else if ( e.type == sf::Event::MouseButtonPressed )
    {
        if ( e.mouseButton.button == sf::Mouse::Left )
        {
            Location loc = getMouseLocation();

            if ( loc == Location::SHOP )
            {
                shop.event_handler(e, sf::Mouse::getPosition(gameWindow));
                *mouseHolding = shop.getSelectedTower();
            }
            else if ( loc == Location::MAP )
            {
                if ( shop.hasSelectedProduct() )
                {
                    if ( shop.buySelectedTower(playerGold) )
                    {
                        towers.emplace_back(shop.getSelectedTower(),false);
                        syncTileToMouse(towers.back());
                        infoPlayerGold.setText(dtostr(playerGold));
                    }
                    else
                    {
                        alert.setText("NOT ENOUGH GOLD!");
                        currentInformation = alert;
                    }
                    *mouseHolding = emptyTile;
                    shop.returnProduct();
                }
                else
                {
                    for ( int a = 0; a < towers.size(); a++ )
                    {
                        if ( towers[a].isMouseInside(sf::Mouse::getPosition(gameWindow)))
                        {
                            currentInformation = towers[a].getInformation();
                            towers[a].flipVisibility();
                            break;
                        }
                    }
                    for ( int a  = 0; a < enemies.size(); a++ )
                    {
                        if ( enemies[a]->isMouseInside(sf::Mouse::getPosition(gameWindow)) )
                        {
                            currentInformation = enemies[a]->getInformation();
                            break;
                        }
                    }
                }
            }
        }
        else if ( e.mouseButton.button == sf::Mouse::Right )
        {
            if ( shop.hasSelectedProduct() )
            {
                *mouseHolding = emptyTile;
                shop.returnProduct();
            }
        }
    }

}
