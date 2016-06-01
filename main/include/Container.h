#pragma once
#include <vector>
#include "Object.h"

namespace labgame
{
    class Actor;
    class Container : public virtual Object
    {
        private:
        std::vector<Object*> inventory;
        Actor* owner;
        int _size = 0;
        
        const int max_size = 0;
        
        public:
        Container(std::string, int);
        
        bool add_item(Object*);
        bool remove(std::string);
        
        int size() const;
        
        virtual void pick_up(Actor *);
        
        std::string get_items_as_text() const;
        virtual void drop();
        
    };
}