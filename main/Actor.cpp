#include <math.h>
#include <functional>
#include <utility>
#include <stdexcept>

#include "Object.h"
#include "Actor.h"
#include "Equippable.h"
#include "LockedRoom.h"


namespace labgame
{
    
    Actor::Actor(int hp)
    {
        this->_hp = hp;
    }
    
    Actor::~Actor()
    {
        for (std::vector<Object*>::const_iterator i = inventory.begin();
        i != inventory.end(); ++i) 
        {
            free (*i);
        }
    }
    
    void Actor::take_damage(int damage, std::string source)
    {
        int reduction = 0;
        if(this->armor != nullptr)
        {
            reduction += this->armor->Damage_Reduction();
        }
        if(this->hat != nullptr)
        {
            reduction += this->hat->Damage_Reduction();
        }
        if(this->boots != nullptr)
        {
            reduction += this->boots->Damage_Reduction();
        }
        damage = damage - reduction < 0 ? 0 : damage - reduction;
        
        this->_hp -= (damage);
        
        //Uncomment this for damage logging
        std::cout << this->full_name() << " took " << damage <<
        " damage from" << source << ". Health is now " << hp() << std::endl;
        
        if(this->hp() <= 0)
        {
            this->die();   
        }
    }
    
    void Actor::die() 
    {
        current_location->leave(this);
        weapon = nullptr;
        hat = nullptr;
        armor = nullptr;
        boots = nullptr;
        extra = nullptr;
        for (std::vector<Object*>::const_iterator i = inventory.begin();
        i != inventory.end(); ++i) 
        {
            current_location->drop(*i);
        }
        
        current_location = nullptr;
        
    }
    
    std::string Actor::full_name() const
    {
        return this->name() + " the " + this->type();
    }
    
    void Actor::equip(int item_id)
    {
        //Will throw error if id is invalid
        Object* item = inventory.at(item_id); 
        
        if(Weapon* w = dynamic_cast<Weapon*>(item))
        {
            this->weapon = w;
        }
        else if(Armor* a = dynamic_cast<Armor*>(item))
        {
            switch(a->Type())
            {
                case Armor::BOOTS:
                    this->boots = a;
                    break;
                case Armor::ARMOR:
                    this->armor = a;
                    break;
                case Armor::HAT:
                    this->hat = a;
                    break;
                default:
                    throw std::out_of_range("Cant find armor type");
            }
        }
        else if(Equippable* e = dynamic_cast<Equippable*>(item))
        {
            this->extra = e;
        }
    }
    
    void Actor::melee_attack(Actor* a) const
    {
        int bonus = 0;
        if(this->weapon != NULL)
        {
            bonus += this->weapon->Damage();
        }
        
        int damage = (std::rand() % ( this->strength < 1 ? 1 : this->strength )) + 1 + bonus;
        std::cout << this->full_name() << " hits " << a->full_name() << " for " << damage << " damage!" << std::endl;
        a->take_damage(damage, "Melee");
        
    }
    
    //Inventory size formula: floor( sqrt(x) + x^1.2)
    int Actor::max_inventory_size() const
    {
        return (floor(pow(this->strength, 0.5) + pow(this->strength, 1.2)));
    }
    
    void Actor::use_ability(std::function<void(Actor*)> lambda, Actor* target)
    {
        lambda(target);
    }
    
    bool Actor::inventory_is_full() const
    {
        return (inventory.size() == max_inventory_size());
    }
    
    void Actor::move_to(Environment* e)
    {
        this->current_location = e;
        e->enter(this);
    }
    
    bool Actor::pick_up(std::string s)
    {
        Object * i = current_location->get_item(s);
        
        if (i == nullptr)
        {
            return false;
        }
        
        if (!inventory_is_full())
        {
            current_location->pick_up(s);
            inventory.push_back(std::move(i));
            return true;
        }
        return false;
        
    }
    
    bool Actor::has_item(std::string name) const
    {
        std::cout << "Checking if has item " << name << std::endl;
        for (std::vector<Object* >::const_iterator i = inventory.begin();
        i != inventory.end(); ++i) 
        {
            std::cout << "Looping once" << std::endl;
            if((*i)->Name() == name)
            {
                std::cout << "Have item" << std::endl;
                return true;
            }
        }
        std::cout << "Doesnt have item" << std::endl;
        return false;
    }
    
    void Actor::unlock(std::string dir)
    {
        std::cout << "In actor unlock" << std::endl;
        LockedRoom* r = dynamic_cast<LockedRoom*>(current_location);
        if(r != nullptr)
        {
            r->unlock(this, dir);
        }
        
        std::pair<Environment*, std::string> p = current_location->get_neighbour_and_out(dir);
        LockedRoom* rNext = dynamic_cast<LockedRoom*>(p.first);
        std::string out = p.second;
        
        if(rNext != nullptr)
        {
            rNext->unlock(this, out);
        }
    }
    
    void Actor::use_item(int item_id)
    {
        std::cout << "Using item " << item_id << std::endl;
        if (item_id > this->inventory.size() - 1 || item_id < 0)
        {
            return;
        }
        this->inventory[item_id]->use();
    }
    
    bool Actor::is_equippable(int item_id) const
    {
        std::cout << "Checking if equippable" << std::endl;
        if(item_id < 0 || item_id > inventory.size()-1)
        {
            throw std::out_of_range("Too big id in is_equippable");
        }
        Equippable* e = dynamic_cast<Equippable *>(inventory.at(item_id));
        return (e!=nullptr);
    }
    
    void Actor::go(std::string direction)
    {
        std::clog << "in go" << std::endl;
        std::pair<Environment*, std::string> p = this->current_location->get_neighbour_and_out(direction);
        Environment* e = p.first;
        std::string eOut = p.second;
        
        std::clog << "e is " << e << std::endl;
        
        if(e == nullptr)
        {
            std::cout << "Null room" << std::endl;
            return;
        }
        std::clog << "Curren loc: " << current_location << std::endl;
        if(current_location != nullptr)
        {
            if(!current_location->can_leave(this, direction))
            {
                std::cout << "You cant leave  " << current_location->get_id() << std::endl;
                return;
            }
        }
        
        std::clog << "Checking if can enter" << std::endl;
        
        if(!e->can_enter(this, eOut))
        {
            std::cout << "You cant enter " << e->get_id() << std::endl;
            return;
        }
        
        std::clog << "Can enter" << std::endl;
        
        //Else
        if(current_location != nullptr)
        {
            std::clog << "Leaving current" << std::endl;
            current_location->leave(this);
        }
        std::clog << "Changing current" << std::endl;
        current_location = e;
        current_location->enter(this);
        
        //DEBUG!
        std::cout << full_name() << " is now in room with id " << current_location->get_id() << std::endl;
    }
}