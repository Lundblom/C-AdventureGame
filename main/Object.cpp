#include <string>
#include "Object.h"
#include "MapParser.h"

namespace labgame
{
    Object::Object(std::string _name) : name(_name)
    {
        
    }
    
    Object::~Object()
    {
        
    }
    
    void Object::use()
    {
    }
    
    std::string Object::get_as_serializable(std::string location) const
    {
        std::string result;
        
        result += MapParser::OBJECT_NAME;
        result += MapParser::SPECIFIER_DELIMETER;
        result += location;
        result += MapParser::DELIMETER;
        result += Name();
        result += MapParser::DELIMETER;
        
        return result; 
    }
    
    void Object::drop()
    {
        this->owner = nullptr;
    }
    
    void Object::pick_up(Actor* a)
    {
        owner = a;
    }
}