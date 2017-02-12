#ifndef INGAME_H
#define INGAME_H

#include "enemy.h"
#include <vector>
#include "MapManager.h"
#include "resourcemanager.h"
#include "Tower.h"
#include <memory>
#include "FileLoader.h"
#include <SFML/Graphics.hpp>
#include <map>
#include "uicomponent.h"
#include "Shop.h"
#include <algorithm>
#include <sstream>
#include <string>
#include "wave.h"
class InGame : public FileLoader
{
    public:
        bool isDone()
        {
            return isGameOver;
        }
        InGame(const MapManager& mManager, sf::RenderWindow& window)
            : currMap(mManager.getCurrMap()), startingPos(mManager.getCurrMapStartingPosition()),
             gameWindow(window),
             shop(), mLoc(Location::NONE), playerGold(500), life(10), score(0),
             infoPlayerGold("Gold: " + dtostr(playerGold)), infoLife("Life: " + dtostr(life)), infoScore("Score: " + dtostr(score)),emptyTile("frame.png",sf::Vector2f(0,0),sf::IntRect(0,0,32,32),Boundary()),
             leakPoint(mManager.getLeakPoint()), isGameOver(false)
        {
            mouseHolding = new Entity(emptyTile);
            infoLife.setPosition(infoPlayerGold.getPositionUnderThis());
            infoScore.setPosition(infoLife.getPositionUnderThis());
            boundaries.emplace_back(Location::MAP);
            boundaries.emplace_back(Location::SHOP);
            boundaries.emplace_back(Location::INFORMATION);
            wave.setInfoPosition(infoScore.getPositionUnderThis());
        }
        void draw();
        void update(double delta);
        void event_handler(sf::Event e);
        ~InGame() { delete mouseHolding; }
        bool load(const std::string& filename) // load ui
        {
            fOpener.open("ui.txt");
            if ( fOpener.is_open() )
            {
                std::string data;
                int a = 0;
                Location strToLoc = NONE;
                while ( fOpener >> data )
                {
                    std::array<std::string,3>::const_iterator found = std::find(locNames.begin(),locNames.end(),data);
                    if ( found != locNames.end() )
                    {
                        if ( strToLoc != NONE )
                            boundaries[a].calculateBoundaries();
                        strToLoc = (Location)(found - locNames.begin());
                        for ( a = 0; a < boundaries.size(); a++ )
                        {
                            if ( boundaries[a].isLocatedHere(strToLoc) )
                            {
                                fOpener >> data;
                                break;
                            }
                        }
                    }
                    sf::Vertex vertex;
                    vertex.position.x = stod(data);
                    fOpener >> data;
                    vertex.position.y = stod(data);
                    boundaries[a].append(vertex);
                }
                boundaries[a].calculateBoundaries();
                std::cout << boundaries.size();
                shop.setBoundary(boundaries[SHOP]);
                shop.arrangeProducts(boundaries[INFORMATION]);
                alert.setInfoBoundary(boundaries[INFORMATION]);
            }
            fOpener.close();
        }

    private:
        std::array<std::string,3> locNames { {"MAP", "SHOP", "INFORMATION"} };

        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<Tower> towers;

        const sf::VertexArray& currMap;
        const sf::Vector2f& startingPos;
       int leakPoint;
        sf::RenderWindow& gameWindow;

        Entity* mouseHolding;
        Entity emptyTile;

        Wave wave;
        Information currentInformation;

        Location mLoc;

        void syncTileToMouse(Entity& ent);

        double playerGold;
        double life;
        double score;

        Information infoPlayerGold;
        Information infoLife;
        Information infoScore;

        Information alert;
        Shop shop;

        std::string dtostr(double d)
        {

            std::ostringstream ss;
            ss << d;
            return ss.str();
        }

        Location getMouseLocation();

        std::vector<Boundary> boundaries;

        bool isGameOver;

        sf::Clock timerForSpawn;
        sf::Clock timerForWave;

};

#endif // INGAME_H
