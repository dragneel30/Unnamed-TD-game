#include "FileLoader.h"

FileLoader::FileLoader()
{
    //ctor
}
double stod(const std::string& str)
{
    std::istringstream convert(str);
    double d;
    convert >> d;
    return d;
}
