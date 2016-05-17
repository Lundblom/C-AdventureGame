#include <string>
#include "Equippable.h"
#pragma once

namespace labgame
{
    class Weapon : public Equippable
    {
        int damage;
        public:
        Weapon(std::string, int);
        void attack_effect();
        
        int Damage() const {return damage;}
        
        virtual void use() override;
    };
}