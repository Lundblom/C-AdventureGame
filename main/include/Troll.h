#include <string>
#include "NPC.h"

namespace labgame
{
    class Troll : public NPC
    {
        private:
        
        virtual void die();

        const int HEALTH = 31;
        const double TANTRUM_MULTIPLIER = 1.5;
        
        
        //Keeps track of when the troll throws a tantrum / when it ends
        int rageCounter = 0;
        bool tantrum = false;
        
        const static int TIME_UNTIL_RAGE = 5;
        const static int TIME_RAGE_LASTS = 2;
        
        protected:
        void throw_tantrum();
        public:
        Troll(std::string);
        
        void action() override;
        virtual std::string type() const override;
        
        virtual void fight(Actor *);
    };
}