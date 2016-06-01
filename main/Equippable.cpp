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
    
    Equippable::Equippable(std::string _name, int _strength, int _dexterity, int _constitution, int _intelligence, int _wisdom, int _charisma) : Object(_name)
    {
        
    }
}