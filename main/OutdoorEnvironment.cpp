#include "Environment.h"
#include "OutdoorEnvironment.h"

namespace labgame
{
    OutdoorEnvironment::OutdoorEnvironment(int _id, Weather::TYPE t) :  
        Environment(_id), weather(t)
    {
    }
    
    OutdoorEnvironment::~OutdoorEnvironment()
    {
        
    }
    
    int OutdoorEnvironment::get_weather_number() const
    {
        return weather.get_weather_number();
    }
    
    void OutdoorEnvironment::wait(Actor * a)
    {
        weather.effect(a);
    }
    
    void OutdoorEnvironment::enter(Actor * a)
    {
        Environment::enter(a);
        weather.effect(a);
    }
    
    std::string OutdoorEnvironment::description() const
    {
        return weather.description();
    }
}