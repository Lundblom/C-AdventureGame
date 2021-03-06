#pragma once
#include "IndoorEnvironment.h"
#include <vector>
namespace labgame
{
    class LockedRoom : public IndoorEnvironment
    {
        private:
        
        const int NEIGHBOURS = 4;
        const std::string room_description = "Just an ordinary room.";
        
        std::vector<std::string> locked_directions;
        std::map<std::string, std::string> required_items;
        
        
        protected:
        
        public:
        LockedRoom(int _id, std::string _desc,
            std::vector<std::pair<std::string, std::string>> l);
        virtual ~LockedRoom();
        
        bool unlock(Actor* a, std::string);
        
        bool is_locked(std::string) const;
        
        
        virtual std::string description() const override;
        
        virtual std::string get_as_serializable() const override;
        
        virtual bool can_enter(Actor*, std::string) override;
        virtual bool can_leave(Actor*, std::string) override;
        virtual void wait(Actor*) override;
    };
}