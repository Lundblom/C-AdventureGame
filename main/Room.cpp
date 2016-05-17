#include "Room.h"

namespace labgame
{
    Room::Room(int _id) : IndoorEnvironment(_id)
    {
        max_neighbours = NEIGHBOURS;
    }
    
    Room::Room(int _id, std::string _desc) : IndoorEnvironment(_id), room_description(_desc)
    {
        max_neighbours = NEIGHBOURS;
    }
    
    std::string Room::description() const
    {
        std::string ret = "This is a room. ";
        ret += room_description;
        return ret;
    }
    
    void Room::enter(Actor * a)
    {
        
    }
    
    void Room::leave(Actor * a)
    {
        
    }
}