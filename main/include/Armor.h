#include <string>
#include "Equippable.h"
#pragma once

namespace labgame
{
    class Armor : public Equippable
    {
        public:
        enum ARMOR_TYPE
        {
            HAT,
            ARMOR,
            BOOTS
        };
        private:
        int damage_reduction;
        ARMOR_TYPE type;
        public:
        
        ARMOR_TYPE Type() const {return type;}
        
        Armor(std::string, int, ARMOR_TYPE);
        void defense_effect();
        
        int Damage_Reduction() const {return damage_reduction;}
        virtual std::string get_as_serializable(std::string) const override;
        
        virtual void use() override;
    };
}