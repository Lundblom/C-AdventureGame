#pragma once
#include "Object.h"
namespace labgame
{
    class Equippable : public Object
    {
        private:
        int _damage = 0;
        int _armor = 0;
        
        public:
        
        int Damage() {return this->_damage;}
        int Armor() {return this->_armor;}
        
        virtual void use() override;
    };
}