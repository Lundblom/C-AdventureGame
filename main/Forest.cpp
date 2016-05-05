#include "Forest.h"
#include "Room.h"

namespace labgame
{
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
    
    void Forest::enter(Actor * a)
    {
    }
    
    void Forest::leave(Actor * a)
    {
    }
}