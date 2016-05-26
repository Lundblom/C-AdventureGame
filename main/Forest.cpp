#include "Forest.h"
#include "OutdoorEnvironment.h"
#include "Room.h"

namespace labgame
{
    
    const int Forest::FOREST_HEAL = 1;
    Forest::Forest(int _id, Weather::TYPE t) : OutdoorEnvironment(_id, t)
    {
        max_neighbours = NEIGHBOURS;
    }
    
    Forest::Forest(int _id, std::string _desc, Weather::TYPE t) : OutdoorEnvironment(_id, t), room_description(_desc)
    {
        max_neighbours = NEIGHBOURS;
    }
    
    std::string Forest::description() const
    {
        std::string ret = "This is a forest. ";
        ret += room_description;
        ret += "\n";
        ret += OutdoorEnvironment::description();
        return ret;
    }
    
    void Forest::wait(Actor * a)
    {
        OutdoorEnvironment::wait(a);
        a->heal_damage(FOREST_HEAL, "forest heal");
    }
}