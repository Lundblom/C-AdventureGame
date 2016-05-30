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
        const static std::string CLEAR_DESC;
        const static std::string RAIN_DESC;
        const static std::string SNOW_DESC;
        const static std::string ACIDRAIN_DESC;
        public:
        
        Weather(TYPE);
        ~Weather();
        
        std::string description() const;
        
        void effect(Actor *);
        
        
    };
}