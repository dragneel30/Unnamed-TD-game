#ifndef FILELOADER_H
#define FILELOADER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>

class FileLoader
{
    public:
        FileLoader();
        virtual bool load(const std::string& filename) = 0;
    protected:
        std::ifstream fOpener;
};

double stod(const std::string& str);

#endif // FILELOADER_H
