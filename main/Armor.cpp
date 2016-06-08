#include "Armor.h"
#include "MapParser.h"
namespace labgame
{
    Armor::Armor(std::string _name, int _damage_reduction, ARMOR_TYPE _type) : 
        Object(_name), Equippable(_name), type(_type), damage_reduction(_damage_reduction)
    {
        
    }
    
    void Armor::use()
    {
        
    }
    
    std::string Armor::get_as_serializable(std::string location) const
    {
        std::string result;
        
        result += MapParser::ARMOR_NAME;
        result += MapParser::DELIMETER;
        result += location;
        result += MapParser::DELIMETER;
        result += damage_reduction;
        result += MapParser::DELIMETER;
        result += std::to_string((int)type);
        result += MapParser::DELIMETER;
    }
}