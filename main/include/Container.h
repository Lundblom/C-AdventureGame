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
        int _size = 0;
        
        const int max_size = 0;
        
        public:
        Container(std::string, int);
        virtual ~Container();
        
        bool add_item(Object*);
        bool remove(std::string);
        
        int size() const;
        std::string get_items_as_text() const;
        virtual std::string get_as_serializable(std::string) const override;
        
    };
}