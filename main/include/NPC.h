#pragma once
namespace labgame
{
    class NPC : public Actor
    {
        public:
        enum Temper
        {
            CALM,
            PASSIVE,
            AGRESSIVE,
            AFRAID
        };
        private:
        
        bool friendly;
        Temper temper;
        
        public: 
        
        NPC(Temper,int, std::string);
        NPC();
        ~NPC();
        
        virtual void die() override;
        
        
        virtual std::string type() const override;
        virtual std::string comparable_type() const override;
        
        
        
    };
}