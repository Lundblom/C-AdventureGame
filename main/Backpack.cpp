#include "Backpack.h"

namespace labgame
{
    Backpack::Backpack(std::string _name, int size, int _strength, int _dexterity, int _constitution, int _intelligence, int _wisdom, int _charisma) : Container(_name, size), Equippable(_name, _strength, _dexterity, _constitution, _intelligence, _wisdom, _charisma), Object(_name)
    {
        
    }
    
    
}