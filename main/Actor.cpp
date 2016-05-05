#include <math.h>
#include <functional>

#include "Object.h"
#include "Actor.h"


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
            reduction += this->armor->Armor();
        }
        if(this->hat != nullptr)
        {
            reduction += this->hat->Armor();
        }
        if(this->boots != nullptr)
        {
            reduction += this->boots->Armor();
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
    
    void Actor::use_item(int item_id)
    {
        if(item_id > this->inventory.size() - 1)
        {
            std::cout << "That is not a valid id." << std::endl;
            return;
        }
        
        this->inventory[item_id]->use();
    }
    
    void Actor::go(std::string direction)
    {
        Environment * e = this->current_location->neighbour(direction);
        
        if(e == nullptr)
        {
            return;
        }
        //Else
        if(current_location != nullptr)
        {
            current_location->leave(this);
        }
        current_location = e;
        current_location->enter(this);
    }
}