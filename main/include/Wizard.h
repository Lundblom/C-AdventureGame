#include "Actor.h"
#include "Player.h"
#include "Spell.h"
#pragma once
namespace labgame
{
    class Wizard : public Player
    {
        private:

        static const std::map<std::string, Spell> all_spells;
        
        std::vector<std::string> known_spells;
        
        protected:
        void cast_spell(Actor*);
        
        public:
        
        static const int STARTING_HP;
        static const int STARTING_MP;
        static const int DEFAULT_INTELLIGENCE;
        static const int DEFAULT_STRENGTH;
        
        Wizard(std::string, int);
        
        virtual void fight(Actor *) override;
        virtual std::string type() const;
    };
}