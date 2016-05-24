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
        
        
        void display_inventory() const;
        
        public:
        
        Player(std::string, int);
        
        void add_alias(std::string, std::string);
        void examine();
        void examine(Object&);
        virtual std::string type() const = 0;
        virtual std::string comparable_type() const;
        virtual void fight(Actor*) override;
        
        virtual bool pick_up(std::string) override;
        
        void inspect();
        
        //Wrapper functions
        void use_item_p();
        void go_p(std::string*);
        void pick_up_p(std::string*);
        void unlock_p(std::string*);
        void drop_p(std::string*);
        
        void talk_to(Actor *);
        
        virtual void action();
    };
}