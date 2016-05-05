#include "global.h"
#include <iostream>
namespace labgame
{
    std::map<std::string, Actor *> global::actor_map;
    
    void global::add_actor(std::string name, Actor * a)
    {
        actor_map[name] = a;
    }
    Actor * global::get_actor(std::string name)
    {
        auto it = actor_map.find(name);
        Actor * ret;
        if (it == actor_map.end())
        {
            ret = nullptr;
        }
        else
        {
            ret = it->second;
        }
        
        
        return ret;
    }
}