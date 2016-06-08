#pragma once
#include "Object.h"
namespace labgame
{
    class HealthPotion : public virtual Object
    {
        private:
        const int healing_amount = 0;
        const int uses = 1;
        int times_used = 0;
        
        public:
        
        HealthPotion(std::string, int, int);
        virtual ~HealthPotion();
        
        virtual std::string get_as_serializable(std::string) const override;
        
        virtual void use() override;
    };
}