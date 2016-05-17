#include <math.h>
#include <functional>
#include <utility>
#include <stdexcept>

#include "Object.h"
#include "Actor.h"
#include "Equippable.h"


namespace labgame
{
    
    Actor::Actor(int hp, Environment* start_position)
    {
        this->_hp = hp;
        start_position->enter(this);
        current_location = start_position;
        
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
        /*std::cout << this->full_name() << " took " << damage <<
        " damage from" << source << std::endl; */
        
        if(this->hp() >= 0)
        {
            this->die();   
        }
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
        a->take_damage(damage, "Melee");
        std::cout << this->full_name() << " hits " << a->full_name() << " for " << damage << " damage!" << std::endl;
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
        for (std::vector<Object* >::const_iterator i = inventory.begin();
        i != inventory.end(); ++i) 
        {
            if((*i)->Name() == name)
            {
                return true;
            }
        }
        return false;
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
        std::pair<Environment*, std::string> p = this->current_location->get_neighbour_and_out(direction);
        Environment* e = p.first;
        std::string eOut = p.second;
        
        std::cout << "Trying to go to " << e->get_id() << std::endl;
        if(e == nullptr)
        {
            std::cout << "Null room" << std::endl;
            return;
        }
        if(current_location != nullptr)
        {
            if(!current_location->can_leave(this, direction))
            {
                std::cout << "You cant leave  " << current_location->get_id() << std::endl;
                return;
            }
        }
        
        
        if(!e->can_enter(this, eOut))
        {
            std::cout << "You cant enter " << e->get_id() << std::endl;
            return;
        }
        
        
        //Else
        if(current_location != nullptr)
        {
            current_location->leave(this);
        }
        current_location = e;
        current_location->enter(this);
        
        //DEBUG!
        std::cout << full_name() << " is now in room with id " << current_location->get_id() << std::endl;
    }
}