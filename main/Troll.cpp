#include <random>
#include <cmath>

#include "Actor.h"
#include "NPC.h"
#include "Troll.h"
#include "Player.h"

void labgame::Troll::die()
{
    std::cout << "A troll died!" << std::endl;
}

void labgame::Troll::action()
{
    //Handle tantrum counting first
    if(tantrum)
    {
        rageCounter--;
        if(rageCounter == 0)
        {
            tantrum = false;
        }
    }
    else
    {
        rageCounter++;
        if(rageCounter == TIME_UNTIL_RAGE);
        {
            tantrum = true;
            rageCounter = TIME_RAGE_LASTS;
        }
    }
    
    Actor * p = current_location->get_first_visitor_of_type<Player>();
    
    if(p != nullptr)
    {
        fight(p);
    }
    else
    {
        //Go somewhere randomly
        std::vector<std::string> dirs = current_location->directions();
        int r = rand() % (dirs.size() - 1);
        this->go(dirs[r]);
    }
    
    
    
}

labgame::Troll::Troll(std::string _name, Environment* start_position) : NPC(NPC::AGRESSIVE, HEALTH, _name, start_position)
{
}


std::string labgame::Troll::type() const
{
    return "Troll";
}

void labgame::Troll::fight(Actor * a)
{
    melee_attack(a);
}