#include <iostream>
#include "Actor.h"
#include "global.h"

#include "NPC.h"

namespace labgame
{
    
    NPC::NPC(NPC::Temper temper, int hp, std::string _name, Environment* start_position) : Actor(hp, start_position)
    {
        this->temper = temper;
        this->_name = _name;
        global::add_actor(this->name(), this);
    }
    NPC::NPC(Environment* start_position) : Actor(1, start_position)
    {
        this->temper = NPC::CALM;
        this->_name = _name;
        global::add_actor(this->name(), this);
    }
    
    std::string NPC::type() const
    {
        return "NPC";
    }
}