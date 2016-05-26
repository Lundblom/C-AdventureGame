#pragma once

#include "Actor.h"
namespace labgame
{
    class Actor;
    class Weather
    {
        
        public: 
        enum TYPE
        {
            CLEAR,
            RAIN,
            SNOW,
            ACIDRAIN,
        };
        private:
        TYPE type;
        std::string desc;
        const static int ACID_DAMAGE;
        public:
        
        Weather(TYPE);
        
        std::string description() const;
        
        void effect(Actor *);
        
        
    };
}