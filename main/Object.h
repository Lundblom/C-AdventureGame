#pragma once
namespace labgame
{
    class Object
    {
        public:
        Object();
        
        virtual void use() = 0;
    };
}