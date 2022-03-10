#include <iostream>
#include <random>
#include <ctime>
 
class KeyGeneration
{
    std::string Key;

    public:
    KeyGeneration();
    ~KeyGeneration();
    std::string getKey();
};