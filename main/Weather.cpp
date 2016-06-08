#include <iostream>
#include <stdexcept> 
#include "Weather.h"


namespace labgame
{
    const std::string Weather::CLEAR_DESC = "It is clear here.";
    const std::string Weather::RAIN_DESC = "It is raining here.";
    const std::string Weather::SNOW_DESC = "It is snowing here.";
    const std::string Weather::ACIDRAIN_DESC = "It is raning acid here!";
    const int Weather::ACID_DAMAGE = 2;
    
    
    Weather::Weather(TYPE t) : type(t)
    {
        switch(t)
        {
            case CLEAR:
                desc = CLEAR_DESC;
                break;
            case RAIN:
                desc = RAIN_DESC;
                break;
            case SNOW:
                desc = SNOW_DESC;
                break;
            case ACIDRAIN:
                desc = ACIDRAIN_DESC;
                break;
            default:
                std::cerr << "INCORRECT TYPE IN WEATHER " << this << " " << type << std::endl;
                throw std::out_of_range("INCORRECT TYPE");
        }
    }
    Weather::~Weather()
    {
        desc = "";
    }
    
    std::string Weather::description() const
    {
        return desc;
    }
    
    int Weather::get_weather_number() const
    {
        return type;
    }
    
    void Weather::effect(Actor * a)
    {
        switch(type)
        {
            case CLEAR:
                break;
            case RAIN:
                break;
            case SNOW:
                break;
            case ACIDRAIN:
                a->take_damage(ACID_DAMAGE, "acid rain");
                break;
            default:
                std::cerr << "INCORRECT TYPE IN WEATHER " << this << " " << type << std::endl;
                throw std::out_of_range("INCORRECT TYPE");
        }
    }
}