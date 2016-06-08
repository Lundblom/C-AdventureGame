#include "Forest.h"
#include "OutdoorEnvironment.h"
#include "Room.h"
#include "MapParser.h"

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
    
    std::string Forest::get_as_serializable() const
    {
        std::string result;
        
        result += MapParser::FOREST_NAME;
        result += MapParser::SPECIFIER_DELIMETER;
        result += std::to_string(get_id());
        result += MapParser::DELIMETER;
        result += room_description;
        result += MapParser::DELIMETER;
        result += std::to_string(weather.get_weather_number());
        return result;
    }
    
    void Forest::wait(Actor * a)
    {
        OutdoorEnvironment::wait(a);
        a->heal_damage(FOREST_HEAL, "forest heal");
    }
}