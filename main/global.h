#include <map>
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
        static Actor * get_actor(std::string);
    };
    
    
}