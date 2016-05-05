#pragma once

#include "Weather.h"
#include "Environment.h"

namespace labgame
{
    class OutdoorEnvironment : public Environment
    {
        private:
       
        
        Weather* weather;    
        
        protected:
        OutdoorEnvironment(int);
        
        public:
    };
}