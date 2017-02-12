#include "Assets.h"

std::string towers[]
{
    "tower1.png"
};

std::string enemies[]
{
    "bandit.png"
};

std::size_t getArrayLength(std::string arr[])
{
    return (sizeof(arr) / sizeof(std::string));
}
