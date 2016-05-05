#include "Actor.h"
#include "Player.h"
#include "Spell.h"
#pragma once
namespace labgame
{
    class Wizard : public Player
    {
        private:
        
        const int STARTING_HP = 13;
        const int STARTING_MP = 50;
        
        std::map<std::string, Spell*> spell_map;
        
        protected:
        void cast_spell(Actor*);
        
        public:
        
        Wizard(std::string name, Environment*);
        
        virtual void fight(Actor *) override;
        virtual std::string type() const;
    };
}