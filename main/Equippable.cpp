#include "Equippable.h"
#include <iostream>

namespace labgame
{
    void Equippable::use()
    {
        std::cout << "it was used" << std::endl;
    }
    
    Equippable::Equippable(std::string _name) : Object(_name)
    {
        
    }
}