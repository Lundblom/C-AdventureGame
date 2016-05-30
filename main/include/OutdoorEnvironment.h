#pragma once

#include "Weather.h"
#include "Environment.h"

namespace labgame
{
    class OutdoorEnvironment : public Environment
    {
        private:
        Weather weather;    
        
        protected:
        OutdoorEnvironment(int, Weather::TYPE);
        virtual ~OutdoorEnvironment();
        
        public:
        virtual void wait(Actor* ) override;
        virtual void enter(Actor *) override;
        
        virtual std::string description() const override;
    };
}