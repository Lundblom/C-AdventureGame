#include <functional>

#include "Spell.h"
#include "Actor.h"
namespace labgame
{
    
    Spell::Spell(std::function<void(Actor*)> _func, std::string theName, int theCost)
        : function(_func), _name(theName), _cost(theCost)
    {
        
    }
    std::function<void(Actor*)> Spell::get_spell() const
    {
        return this->function;
    }
    
    std::string Spell::name() const
    {
        return this->_name;
    }
    
    int Spell::cost() const
    {
        return this->_cost;
    }
}