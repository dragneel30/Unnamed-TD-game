#include "MapManager.h"

const std::string FILE_EXTENSION = ".txt";

MapManager::MapManager(const std::string& filename)
{
   currMap.setPrimitiveType(sf::Quads);
   load(filename);
}

void MapManager::addMap(const std::string& name)
{
    maps.emplace_back(name);
}

bool MapManager::load(const std::string& name)
{
    if ( isThereLoadedMap() )
    {
        unloadCurrMap();
    }
    if ( std::find(maps.begin(),maps.end(),name) == maps.end() )
    {
        addMap(name);
    }
    fOpener.open(name + FILE_EXTENSION);
    if ( fOpener.is_open() )
    {
        sf::Vector2f pos;
        while(fOpener >> pos.x)
        {
            fOpener >> pos.y;
            currMap.append(pos);
            currMap.append(sf::Vector2f(pos.x+32,pos.y));
            currMap.append(sf::Vector2f(pos.x+32,pos.y+32));
            currMap.append(sf::Vector2f(pos.x,pos.y+32));
        }
    }
    calculateStartingPosition();
    leakPoint = currMap.getVertexCount()-4;
    return isThereLoadedMap();
}

int MapManager::getLeakPoint() const
{
    return leakPoint;
}
bool MapManager::isThereLoadedMap()
{
    return currMap.getVertexCount() > 0;
}

void MapManager::unloadCurrMap()
{
    if ( isThereLoadedMap() )
    {
        currMap.clear();
    }
}

const sf::VertexArray& MapManager::getCurrMap() const
{
    return currMap;
}

const sf::Vector2f& MapManager::getCurrMapStartingPosition() const
{
    return currMapStartingPosition;
}
#include <iostream>
void MapManager::calculateStartingPosition()
{
    sf::Vector2f first = currMap[0].position,
    second = currMap[4].position;
    //std::cout << "(" << first.x << "," << first.y << ")" << " " << "(" << second.x << "," << second.y << ")" << std::endl;
    if ( first.x > second.x )
        first.x += 32;
    else if ( first.x < second.x )
        first.x -= 32;
    else if ( first.y > second.y )
        first.y += 32;
    else if ( first.y < second.y )
        first.y -= 32;

    //std::cout << first.x << " " << first.y << std::endl;
    currMapStartingPosition = first;
}
const std::vector<std::string>& MapManager::getMaps() const
{
    return maps;
}
