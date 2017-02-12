#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include "FileLoader.h"
#include "uicomponent.h"
template<typename T>
class ResourceManager : public FileLoader
{
    public:
        const T& get(const std::string& filename)
        {
            if ( !isConflict(filename) )
            {
                load(filename);
            }
            return resources[filename];
        }

        bool load(const std::string& filename)
        {
            resources[filename] = T();
            return resources[filename].loadFromFile(filename);
        }

        void unload(const std::string& filename)
        {
            resources.erase(filename);
        }

        bool isConflict(const std::string& filename)
        {
            return resources.find(filename) != resources.end();
        }

        static ResourceManager& getInstance()
        {
            static ResourceManager<T> instance;
            return instance;
        }

        void cleanUp()
        {
            resources.clear();
        }
    private:
        std::map<std::string,T> resources;
        ResourceManager() {}
};




#endif // RESOURCEMANAGER_H
