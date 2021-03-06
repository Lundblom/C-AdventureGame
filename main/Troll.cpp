#include <random>
#include <cmath>

#include "Actor.h"
#include "NPC.h"
#include "Troll.h"
#include "Player.h"
#include "MapParser.h"

void labgame::Troll::die()
{
    NPC::die();
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
    
    Actor * p = current_location->get_first_visitor_of_type("Player");
    
    if(p != nullptr)
    {
        fight(p);
    }
    else
    {
        //Go somewhere randomly
        std::vector<std::string> dirs = current_location->directions();
        int r = rand() % (dirs.size());
        this->go(dirs[r]);
    }
}

labgame::Troll::Troll(std::string _name) : NPC(NPC::AGRESSIVE, HEALTH, _name)
{
    inventory.push_back(new Object("COOKIEEEE"));
}

std::string labgame::Troll::get_as_serializable() const
{
    std::string result = "";
    result += MapParser::TROLL_NAME;
    result += MapParser::SPECIFIER_DELIMETER;
    result += std::to_string(current_location->get_id());
    result += MapParser::DELIMETER;
    result += name();
    result += MapParser::DELIMETER;
    result += std::to_string(hp());
    
    return result;
}

std::string labgame::Troll::type() const
{
    return "Troll";
}

void labgame::Troll::fight(Actor * a)
{
    melee_attack(a);
}