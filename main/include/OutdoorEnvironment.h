#pragma once

#include "Weather.h"
#include "Environment.h"

namespace labgame
{
    class OutdoorEnvironment : public Environment
    {
        private:
           
        
        protected:
        OutdoorEnvironment(int, Weather::TYPE);
        Weather weather; 
        virtual ~OutdoorEnvironment();
        
        public:
        virtual void wait(Actor* ) override;
        virtual void enter(Actor *) override;
        int get_weather_number() const;
        
        virtual std::string description() const override;
    };
}