#include <iostream>
#include <stdexcept> 
#include "Weather.h"


namespace labgame
{
    const int Weather::ACID_DAMAGE = 2;
    Weather::Weather(TYPE t) : type(t)
    {
        switch(t)
        {
            case CLEAR:
                desc = "It is clear here.";
                break;
            case RAIN:
                desc = "It is raining here.";
                break;
            case SNOW:
                desc = "It is snowing here";
                break;
            case ACIDRAIN:
                desc = "It is raining acid here!";
                break;
            default:
                std::cerr << "INCORRECT TYPE IN WEATHER " << this << " " << type << std::endl;
                throw std::out_of_range("INCORRECT TYPE");
        }
    }
    
    std::string Weather::description() const
    {
        return desc;
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