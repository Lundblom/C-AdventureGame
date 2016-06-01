#pragma once
#include <string>
namespace labgame
{
    class Actor;
    class Object
    {
        
        private:
        
        std::string name;
        bool useable;
        
        public:
        Object();
        Object(std::string);
        inline std::string Name() const {return this->name;}
        inline bool is_useable() const {return this->useable;}
        
        virtual void use();
        virtual void pick_up(Actor*);
        virtual void drop();
    };
}