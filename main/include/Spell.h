#include <functional>

#include "Actor.h"
#pragma once
namespace labgame
{
    class Spell
    {
        private:
        const std::function<void(Actor*)> function;
        const std::string _name;
        const int _cost = 0;
        
        public:
        Spell(std::function<void(Actor*)>, std::string, int);
        std::string name() const;
        int cost() const;
        std::function<void(Actor*)> get_spell() const;
        
    };
}