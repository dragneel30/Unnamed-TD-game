#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "FileLoader.h"
class MapManager : public FileLoader
{
    public:
        MapManager(const std::string& filename);
        void addMap(const std::string& name);
        bool load(const std::string& name);
        bool isThereLoadedMap();
        void unloadCurrMap();
        const sf::VertexArray& getCurrMap() const;
        const std::vector<std::string>& getMaps() const;
        const sf::Vector2f& getCurrMapStartingPosition() const;
        int getLeakPoint() const;
    private:
        void calculateStartingPosition();
        std::vector<std::string> maps;
        sf::VertexArray currMap;
        sf::Vector2f currMapStartingPosition;
       int leakPoint;
};

#endif // MAPMANAGER_H
