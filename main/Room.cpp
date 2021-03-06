#include "Room.h"
#include "MapParser.h"

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
    
    std::string Room::get_as_serializable() const
    {
        std::string result;
        
        result += MapParser::ROOM_NAME;
        result += MapParser::SPECIFIER_DELIMETER;
        result += std::to_string(get_id());
        result += MapParser::DELIMETER;
        result += room_description;
        
        return result;
    }
    
    void Room::wait(Actor * a)
    {
        
    }
}