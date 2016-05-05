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
        
        NPC(Temper,int, std::string, Environment*);
        NPC(Environment*);
        
        
        virtual std::string type() const override;
        
        
        
    };
}