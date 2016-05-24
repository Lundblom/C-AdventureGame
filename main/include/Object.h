#include <string>
#pragma once
namespace labgame
{
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
    };
}