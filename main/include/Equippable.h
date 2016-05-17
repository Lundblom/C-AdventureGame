#pragma once
#include "Object.h"
namespace labgame
{
    class Equippable : public Object
    {
        private:
        int strength = 0;
        int dexterity = 0;
        int constitution = 0;
        int intelligence = 0;
        int wisdom = 0;
        int charisma = 0;
        
        public:
        Equippable(std::string);
        
        int Strength() const {return strength;}
        int Dexterity() const {return dexterity;}
        int Constitution() const {return constitution;}
        int Intelligence() const {return intelligence;}
        int Wisdom() const {return wisdom;}
        int Charisma() const {return charisma;}
        
        virtual void use() override;
    };
}