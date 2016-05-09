#pragma once
#include <map>
#include <functional>
#include "Object.h"
#include "Actor.h"
namespace labgame
{
    class Player : public Actor
    {
        private:
        
        std::map<std::string, std::function<void()>> command_map;
        std::map<std::string, std::string> alias_map;
        void help();
        
        Actor * actor_target;
        std::string * string_target;
        
        template<class F, class... Args>
        void add_to_map(std::string name, F f, Args&&... args);
        void populate_map();
        
        
        
        protected:
        bool command_successful = true;
        virtual void die();
        
        template<typename S>
        void print_map_options(std::map<std::string, S>);
        
        
        public:
        
        Player(std::string, int, Environment* start_position);
        
        void add_alias(std::string, std::string);
        void examine();
        void examine(Object&);
        virtual std::string type() const = 0;
        virtual void fight(Actor*) override;
        void go(std::string*);
        void inspect();
        
        void talk_to(Actor *);
        
        virtual void action();
    };
}