#pragma once
#include <string>
namespace labgame
{
    class Actor;
    class Object
    {
        friend class MapParser;
        private:
        
        
        std::string name;
        bool useable;
        
        protected:
        Actor* owner;
        bool _no_uses_left = false;
        
        public:
        Object();
        Object(std::string);
        virtual ~Object();
        inline std::string Name() const {return this->name;}
        inline bool is_useable() const {return this->useable;}
        
        inline bool no_uses_left() const {return this->_no_uses_left;}
        
        virtual std::string get_as_serializable(std::string) const;
        
        virtual void use();
        virtual void pick_up(Actor*);
        virtual void drop();
    };
}