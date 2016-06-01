#pragma once
#include "Object.h"
namespace labgame
{
    class Equippable : public virtual Object
    {
        private:
        const int strength = 0;
        const int dexterity = 0;
        const int constitution = 0;
        const int intelligence = 0;
        const int wisdom = 0;
        const int charisma = 0;
        
        public:
        Equippable(std::string);
        Equippable(std::string, int, int, int, int, int, int);
        
        int Strength() const {return strength;}
        int Dexterity() const {return dexterity;}
        int Constitution() const {return constitution;}
        int Intelligence() const {return intelligence;}
        int Wisdom() const {return wisdom;}
        int Charisma() const {return charisma;}
        
        virtual void use() override;
    };
}