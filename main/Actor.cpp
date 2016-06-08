#include <math.h>
#include <functional>
#include <utility>
#include <stdexcept>

#include "Object.h"
#include "Actor.h"
#include "Equippable.h"
#include "LockedRoom.h"
#include "Container.h"
#include "MapParser.h"


namespace labgame
{
    
    Actor::Actor(int hp)
    {
        this->_hp = hp;
        this->maxHp = hp;
    }
    
    Actor::~Actor()
    {
        for (std::vector<Object*>::const_iterator i = inventory.begin();
        i != inventory.end(); ++i) 
        {
            if(*i != nullptr)
            {
                delete (*i);
            }
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
        //std::cout << this->full_name() << " took " << damage <<
        //" damage from " << source << ". Health is now " << hp() << std::endl;
        
        if(_hp <= 0)
        {
            this->die();
        }
    }
    
    void Actor::heal_damage(int amount, std::string source)
    {
        _hp += amount;
        if(_hp > maxHp)
        {
            _hp = maxHp;
        }
        
        std::cout << this->full_name() << " healed " << amount <<
        " damage from " << source << ". Health is now " << hp() << std::endl;
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
        
        inventory.clear();
        
        current_location = nullptr;
        
    }
    
    void Actor::put_in_container(std::string s, std::string t)
    {
        Object * o = find_item_in_inventory(s);
        Object * ot = find_item_in_inventory(t);
        if(o == nullptr || ot == nullptr)
        {
            return;
        }
        
        if(Container * c = dynamic_cast<Container*>(o))
        {
                bool success = c->add_item(ot);
                if(success)
                {
                    find_and_delete_item_in_inventory(t);
                }
        }
    }
    
    void Actor::remove_from_container(std::string s, std::string t)
    {
        Object * o = find_item_in_inventory(s);
        if(o == nullptr)
        {
            return;
        }
        
        if(Container * c = dynamic_cast<Container *>(o))
        {
               c->remove(t);
        }
    }
    
    std::string Actor::full_name() const
    {
        return this->name() + " the " + this->type();
    }
    
    void Actor::equip(std::string s)
    {
        //Will throw error if id is invalid
        Object* item = find_item_in_inventory(s);
        
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
    
    void Actor::unequip(std::string s)
    {
        Object * item = find_item_in_inventory(s);
        
        std::clog << "Checking " << item->Name() << std::endl;
        
        if(item == weapon)
        {
            weapon = nullptr;
        }
        else if(item == armor)
        {
            armor = nullptr;
        }
        else if(item == boots)
        {
            boots = nullptr;
        }
        else if(item = hat)
        {
            hat = nullptr;
        }
        else if (item == extra)
        {
            extra = nullptr;
        }
    }
    
    void Actor::melee_attack(Actor* a) const
    {
        int bonus = 0;
        if(this->weapon != nullptr)
        {
            bonus += this->weapon->Damage();
        }
        
        int damage = (std::rand() % ( this->strength < 1 ? 1 : this->strength )) + 1 + bonus;
        std::cout << this->full_name() << " hits " << a->full_name() << " for " << damage << " damage!" << std::endl;
        a->take_damage(damage, "Melee");
        
    }
    
    Object* Actor::find_item_in_inventory(std::string name)
    {
        for (std::vector<Object*>::const_iterator i = inventory.begin(); 
            i != inventory.end(); ++i) 
        {
            if((*i)->Name() == name)
            {
                return (*i);
            }
        }
        
        return nullptr;
    }
    
    Object* Actor::find_and_delete_item_in_inventory(std::string name)
    {
        Object* val = nullptr;
        for (std::vector<Object*>::iterator i = inventory.begin(); 
            i != inventory.end(); ++i) 
        {
            if((*i)->Name() == name)
            {
                val = *i;
                inventory.erase(i);
                break;
            }
        }
        return val;
    }
    
    void Actor::drop(std::string name)
    {
        Object* item = find_and_delete_item_in_inventory(name);
        
        if(item == nullptr)
        {
            return;
        }
        
        current_location->drop(item);
    }
    
    //Inventory size formula: floor( sqrt (strength) + strength^1.2)
    int Actor::max_inventory_size() const
    {
        return (floor(pow(strength, 0.5) + pow(strength, 1.2)));
    }
    
    void Actor::use_ability(std::function<void(Actor*)> lambda, Actor* target)
    {
        lambda(target);
    }
    
    bool Actor::inventory_is_full() const
    {
        int m = max_inventory_size();
        int n = inventory.size();
        return m == n;
    }
    
    Environment* Actor::get_location() const
    {
        return current_location;
    }
    
    void Actor::move_to(Environment* e)
    {
        if(this->current_location != nullptr)
        {
            this->current_location->leave(this);
        }
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
            i->pick_up(this);
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
    
    bool Actor::put_item(Object* o)
    {
        if(!inventory_is_full())
        {
            inventory.push_back(o);
            return true;
        }
        return false;
    }
    
    void Actor::wait()
    {
        this->current_location->wait(this);
    }
    
    void Actor::unlock(std::string dir)
    {
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
    
    std::string Actor::get_inventory_as_serializable() const
    {
        std::string result;
        
        for (auto i = inventory.begin(); i != inventory.end(); ++i) 
        {
            result += (*i)->get_as_serializable(this->name());
            result += "\n";
        }
        return result;
    }
    
    void Actor::set_hp(int hp)
    {
        _hp = hp;
        if(_hp > maxHp)
        {
            maxHp = hp;
        }
    }
    
    void Actor::use_item(std::string s)
    {
        Object * o = find_item_in_inventory(s);
        if(o == nullptr)
        {
            return;
        }
        
        o->use();
        if(o->no_uses_left())
        {
            find_and_delete_item_in_inventory(s);
            delete o;
        }
    }
    
    bool Actor::is_equippable(Object * o) const
    {
        Equippable* e = dynamic_cast<Equippable *>(o);
        return (e!=nullptr);
    }
    
    void Actor::go(std::string direction)
    {
        std::pair<Environment*, std::string> p = this->current_location->get_neighbour_and_out(direction);
        Environment* e = p.first;
        std::string eOut = p.second;
        
        if(e == nullptr)
        {
            return;
        }
        if(current_location != nullptr)
        {
            if(!current_location->can_leave(this, direction))
            {
                return;
            }
        }
        
        if(!e->can_enter(this, eOut))
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