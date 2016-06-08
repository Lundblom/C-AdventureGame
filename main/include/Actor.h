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
        friend class MapParser;
        private:
        int _hp = 0;
        int maxHp = 0;
        
        void set_hp(int hp);
        
        
        protected:
        std::string _name;
        
        int strength = 0;
        int dexterity = 0;
        int constitution = 0;
        int intelligence = 0;
        int wisdom = 0;
        int charisma = 0;
        
        virtual void die();
        
        std::vector<Object*> inventory;
        
        Environment* current_location = nullptr;
        
        Weapon* weapon = nullptr;
        Armor* hat = nullptr;
        Armor* armor = nullptr;
        Armor* boots = nullptr;
        Equippable* extra = nullptr;
        
        int moveSpeed = 0;
       
        void melee_attack(Actor *) const;
        
        Object* find_item_in_inventory(std::string);
        Object* find_and_delete_item_in_inventory(std::string);
        
        virtual void equip(std::string);
        virtual void unequip(std::string);
        
        public:
        
        virtual std::string get_as_serializable() const = 0;
        std::string get_inventory_as_serializable() const;
        
        Actor(int);
        virtual ~Actor();
        
        std::string name() const {return this->_name;}
        std::string full_name() const;
        virtual std::string type() const = 0;
        virtual std::string comparable_type() const = 0;
        int hp() const {return this->_hp;}
        
        Environment * get_location() const;
        
        virtual int max_inventory_size() const;
        void take_damage(int, std::string);
        void heal_damage(int, std::string);
        
        bool inventory_is_full() const;
        bool is_equippable(Object*) const;
        bool has_item(std::string) const;
        
        bool put_item(Object*);

        void use_ability(std::function<void(Actor*)>, Actor *);
    
        void unlock(std::string dir);    
        void use_item(std::string);
        
        void move_to(Environment*);
        
        void put_in_container(std::string, std::string);
        void remove_from_container(std::string, std::string);
        
        //Define these as pure if needed
        virtual int bonus_damage() const { return 0;}
        virtual int damage_reduction() const { return 0;}
        
        virtual void action() = 0;
        
        virtual void go(std::string direction);
        virtual void fight(Actor *) = 0;
        virtual void wait();
    
        
        
        void drop(std::string);
        virtual bool pick_up(std::string);
        
    };
}