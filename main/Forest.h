#pragma once
#include "OutdoorEnvironment.h"
namespace labgame
{
    class Forest : public OutdoorEnvironment
    {
        private:
        
        const int NEIGHBOURS = 8;
        const std::string room_description = "Just an ordinary forest.";
        

        protected:
        
        public:
        
        Forest(int _id);
        Forest(int _id, std::string _desc);
        
        virtual std::string description() const override;
        virtual void enter(Actor*) override;
        virtual void leave(Actor*) override;
    };
}