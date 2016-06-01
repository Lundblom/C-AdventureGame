#include "Weapon.h"

namespace labgame
{
    Weapon::Weapon(std::string _name, int _damage) :
        Object(_name), Equippable(_name), damage(_damage)
    {
        
    }
    
    void Weapon::use()
    {
        
    }
}