#pragma once
#include "Environment.h"

namespace labgame
{
    class IndoorEnvironment : public Environment
    {
        private:
        
        bool trap_active;
        
        protected:
        
        void trap_effect();
        
        public:
        IndoorEnvironment(int);
    };
}