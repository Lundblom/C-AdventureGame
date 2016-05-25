#include "Forest.h"
#include "Room.h"

namespace labgame
{
    
    const int Forest::FOREST_HEAL = 1;
    Forest::Forest(int _id) : OutdoorEnvironment(_id)
    {
        max_neighbours = NEIGHBOURS;
    }
    
    Forest::Forest(int _id, std::string _desc) : OutdoorEnvironment(_id), room_description(_desc)
    {
        max_neighbours = NEIGHBOURS;
    }
    
    std::string Forest::description() const
    {
        std::string ret = "This is a forest. ";
        ret += room_description;
        return ret;
    }
    
    void Forest::wait(Actor * a)
    {
        a->heal_damage(FOREST_HEAL, "forest heal");
    }
}