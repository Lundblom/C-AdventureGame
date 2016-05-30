#include <iostream>
#include "Actor.h"
#include "global.h"

#include "NPC.h"

namespace labgame
{
    
    NPC::NPC(NPC::Temper temper, int hp, std::string _name) : Actor(hp)
    {
        this->temper = temper;
        this->_name = _name;
        global::add_actor(this->name(), this);
    }
    NPC::NPC() : Actor(1)
    {
        this->temper = NPC::CALM;
        this->_name = _name;
        global::add_actor(this->name(), this);
    }
    
    NPC::~NPC()
    {
    }
    
    void NPC::die()
    {
        Actor::die();
        
        global::remove_actor(this->name(), this);
    }
    
    std::string NPC::type() const
    {
        return "NPC";
    }
    
    std::string NPC::comparable_type() const
    {
        return "NPC";
    }
}