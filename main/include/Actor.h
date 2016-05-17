#pragma once
#include <vector>
#include <functional>

#include "PositionVector.h"
#include "Equippable.h"
#include "Environment.h"
#include "Weapon.h"
#include "Armor.h"

namespace labgame
{
    class Environment;
    class Actor
    {
        private:
        int _hp;
        
        protected:
        std::string _name;
        
        int strength = 0;
        int dexterity = 0;
        int constitution = 0;
        int intelligence = 0;
        int wisdom = 0;
        int charisma = 0;
        
        virtual void die() = 0;
        
        std::vector<Object*> inventory;
        
        Environment* current_location;
        
        Weapon* weapon = nullptr;
        Armor* hat = nullptr;
        Armor* armor = nullptr;
        Armor* boots = nullptr;
        Equippable* extra = nullptr;
        
        int moveSpeed = 0;
       
        void melee_attack(Actor *) const;
        
        void equip(int);
        
        public:
        
        
        Actor(int, Environment*);
        
        std::string name() const {return this->_name;}
        std::string full_name() const;
        virtual std::string type() const = 0;
        int hp() const {return this->_hp;}
        
        virtual int max_inventory_size() const;
        void take_damage(int, std::string);
        
        bool inventory_is_full() const;
        bool is_equippable(int) const;
        bool has_item(std::string) const;

        void use_ability(std::function<void(Actor*)>, Actor *);
        
        void use_item(int);
        
        
        
        //Define these as pure if needed
        virtual int bonus_damage() const { return 0;}
        virtual int damage_reduction() const { return 0;}
        
        virtual void action() = 0;
        
        virtual void go(std::string direction);
        virtual void fight(Actor *) = 0;
        
        
        //void drop(Object&)
        virtual bool pick_up(std::string);
        
    };
}