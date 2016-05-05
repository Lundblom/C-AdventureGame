#pragma once
#include "IndoorEnvironment.h"
namespace labgame
{
    class Room : public IndoorEnvironment
    {
        private:
        
        const int NEIGHBOURS = 4;
        const std::string room_description = "Just an ordinary room.";
        
        
        
        protected:
        
        public:
        
        Room(int _id);
        Room(int _id, std::string _desc);
        
        virtual std::string description() const override;
        virtual void enter(Actor*) override;
        virtual void leave(Actor*) override;
    };
}