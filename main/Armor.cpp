#include "Armor.h"

namespace labgame
{
    Armor::Armor(std::string _name, int _damage_reduction, ARMOR_TYPE _type) : 
        Equippable(_name), type(_type), damage_reduction(_damage_reduction)
    {
        
    }
    
    void Armor::use()
    {
        
    }
}