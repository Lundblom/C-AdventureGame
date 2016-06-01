#include "Container.h"
#include "Object.h"
#include "Actor.h"
#include <iostream>

namespace labgame
{

    Container::Container(std::string _name, int size) : Object(_name), max_size(size)
    {
        
    }
    
    bool Container::add_item(Object* o)
    {
        if(o == this)
        {
            return false;
        }
        if(size() < max_size)
        {
            inventory.push_back(o);
            return true;
        }
        return false;
    }
    
    void Container::pick_up(Actor* a)
    {
        owner = a;
    }
    
    bool Container::remove(std::string name)
    {
        if(owner == nullptr)
        {
            return false;
        }
        
        
        bool successful = false;
        
        for (std::vector<Object*>::iterator i = inventory.begin(); 
        i != inventory.end(); ++i) 
        {
            if((*i)->Name() == name)
            {
                successful = owner->put_item(*i);
                inventory.erase(i);
                break;
            }
        }
        return successful;
    }
    
    std::string Container::get_items_as_text() const
    {
        std::string result;
        
        for (std::vector<Object*>::const_iterator i = inventory.begin(); 
        i != inventory.end(); ++i) 
        {
            result += (*i)->Name();
            result += "\n";
        }
        return result;
    }
    
    void Container::drop()
    {
        this->owner = nullptr;
    }
    
    
    int Container::size() const
    {
        return _size;
    }
}