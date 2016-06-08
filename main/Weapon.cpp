#include "Weapon.h"
#include "MapParser.h"

namespace labgame
{
    Weapon::Weapon(std::string _name, int _damage) :
        Object(_name), Equippable(_name), damage(_damage)
    {
        
    }
    
    std::string Weapon::get_as_serializable(std::string location) const
    {
        std::string result;
        
        result += MapParser::WEAPON_NAME;
        result += MapParser::DELIMETER;
        result += location;
        result += MapParser::DELIMETER;
        result += damage;
        
        return result;
    }
    
    void Weapon::use()
    {
        
    }
}