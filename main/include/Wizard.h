#include "Actor.h"
#include "Player.h"
#include "Spell.h"
#pragma once
namespace labgame
{
    class Wizard : public Player
    {
        private:
        
        int _mp = 0;

        static const std::map<std::string, Spell> all_spells;
        
        std::vector<std::string> known_spells;
        
        protected:
        void cast_spell(Actor*);
        
        public:
        
        static const int STARTING_HP;
        static const int STARTING_MP;
        static const int DEFAULT_INTELLIGENCE;
        static const int DEFAULT_STRENGTH;
        
        int mp() const {
            return _mp;
        }
        
        Wizard(std::string, int);
        Wizard(std::string, int, int, std::vector<std::string>);
        ~Wizard();
        
        virtual std::string get_as_serializable() const override;
        
        virtual void fight(Actor *) override;
        virtual std::string type() const;
    };
}