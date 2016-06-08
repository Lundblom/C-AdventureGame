#pragma once
#include <map>
#include <functional>
#include "Object.h"
#include "Actor.h"
#include "Backpack.h"
namespace labgame
{
    class Player : public Actor
    {
        private:
        
        std::map<std::string, std::function<void()>> command_map;
        std::map<std::string, std::string> alias_map;
        Backpack * backpack = nullptr;

        void help();
        
        Actor * actor_target;
        std::string string_target;
        
        std::string split1;
        std::string split2;
        
        template<class F, class... Args>
        void add_to_map(std::string name, F f, Args&&... args);
        void populate_map();
        
        
        
        protected:
        bool command_successful = true;
        virtual void die();
        
        template<typename S>
        void print_map_options(std::map<std::string, S>);
        
        
        void display_inventory() const;
        
        virtual void equip(std::string) override;
        virtual void unequip(std::string) override;
        
        public:
        
        bool _quit = false;
        
        Player(std::string, int);
        
        void add_alias(std::string, std::string);
        void examine();
        void examine(Object&);
        virtual std::string type() const = 0;
        virtual std::string comparable_type() const;
        virtual void fight(Actor*) override;
        virtual void put_in_container(std::string, std::string);
        virtual void remove_from_container(std::string, std::string);
        
        virtual bool pick_up(std::string) override;
        
        void inspect();
        void quit();
        
        void save(std::string);
        
        
        void use_item(std::string s);;
        
        void talk_to(Actor *);
        
        virtual void action();
    };
}