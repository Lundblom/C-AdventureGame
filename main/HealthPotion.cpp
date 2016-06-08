#include "HealthPotion.h"
#include "Actor.h"
#include "MapParser.h"

namespace labgame
{
    
    HealthPotion::HealthPotion(std::string _name, int _heal, int _uses) : Object(_name), uses(_uses), healing_amount(_heal)
    {
        
    }
    
    HealthPotion::~HealthPotion()
    {
        
    }
    
    std::string HealthPotion::get_as_serializable(std::string location) const
    {
        std::string result;
        
        result += MapParser::HEALTHPOTION_NAME;
        result += MapParser::SPECIFIER_DELIMETER;
        result += location;
        result += MapParser::DELIMETER;
        result += Name();
        result += MapParser::DELIMETER;
        result += std::to_string(healing_amount);
        result += MapParser::DELIMETER;
        result += std::to_string(uses);
        
        return result;
    }
    void HealthPotion::use()
    {
        owner->heal_damage(healing_amount, Name());
        if(++times_used == uses)
        {
            _no_uses_left = true;
        }
    }
}