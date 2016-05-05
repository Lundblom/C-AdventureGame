#include <map>
#include <functional>
#include "Actor.h"

namespace labgame
{
    class global
    {
        private:
        
        static std::map<std::string, Actor *> actor_map;
        static void init();
        
        public:
        static void add_actor(std::string, Actor *);
        static void map_on_actors(std::function<void(Actor*)>);
        static Actor * get_actor(std::string);
    };
    
    
}