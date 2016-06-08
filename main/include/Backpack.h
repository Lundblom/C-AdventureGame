#include "Equippable.h"
#include "Container.h"
#pragma once

namespace labgame
{
    class Backpack : public Container, public Equippable
    {

        public:
        Backpack(std::string, int, int, int, int, int , int, int);
        virtual ~Backpack();
        
        virtual std::string get_as_serializable(std::string) const override;
    };
}