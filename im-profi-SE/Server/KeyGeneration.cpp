#include "./KeyGeneration.h"

    KeyGeneration::KeyGeneration()
    {
        std::mt19937 gen { static_cast<unsigned long>(time(nullptr)) };
        std::vector<std::uniform_int_distribution<> >  ascii =
        {
            std::uniform_int_distribution<>('a', 'z'),
            std::uniform_int_distribution<>('A', 'Z'),
            std::uniform_int_distribution<>('0', '9'),
        };
    ascii.emplace_back(0, ascii.size() - 1);
    std::string password;
    for(std::size_t i = 0; i < 4; ++i) 
    {
        for (std::size_t j = 0; j < 4; ++j) 
        {
            password += static_cast<char>(ascii[ascii.back()(gen)](gen));
        }
        if(i<3)
            password+='-';
        //password += (i < 3 ? '-' : ' ');
    }
 
    Key=password;
    };
    KeyGeneration::~KeyGeneration()
    {
    };
    std::string KeyGeneration:: getKey()
    {
        return Key;
    };