#include "Backpack.h"
#include "MapParser.h"
namespace labgame
{
    Backpack::Backpack(std::string _name, int size, int _strength, int _dexterity, int _constitution, int _intelligence, int _wisdom, int _charisma) : Container(_name, size), Equippable(_name, _strength, _dexterity, _constitution, _intelligence, _wisdom, _charisma), Object(_name)
    {
        
    }
    
    Backpack::~Backpack()
    {
        
    }
    
    std::string Backpack::get_as_serializable(std::string location) const
    {
        std::string result;
        
        result += MapParser::BACKPACK_NAME;
        result += MapParser::SPECIFIER_DELIMETER;
        result += location;
        result += MapParser::DELIMETER;
        result += Name();
        result += MapParser::DELIMETER;
        result += std::to_string(size());
        result += MapParser::DELIMETER;
        result += std::to_string(Strength());
        result += MapParser::DELIMETER;
        result += std::to_string(Dexterity());
        result += MapParser::DELIMETER;
        result += std::to_string(Constitution());
        result += MapParser::DELIMETER;
        result += std::to_string(Intelligence());
        result += MapParser::DELIMETER;
        result += std::to_string(Wisdom());
        result += MapParser::DELIMETER;
        result += std::to_string(Charisma());
        return result;
    }
    
    
}