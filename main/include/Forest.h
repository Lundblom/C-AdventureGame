#pragma once
#include "OutdoorEnvironment.h"
namespace labgame
{
    class Forest : public OutdoorEnvironment
    {
        private:
        
        const static int FOREST_HEAL;
        
        const int NEIGHBOURS = 8;
        const std::string room_description = "Just an ordinary forest.";
        

        protected:
        
        public:
        
        Forest(int _id);
        Forest(int _id, std::string _desc);
        
        virtual std::string description() const override;
        virtual void wait(Actor*) override;
    };
}