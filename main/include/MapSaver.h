#pragma once
#include <string>
#include <vector>
#include "Environment.h"
#include "Player.h"
namespace labgame
{
    class MapSaver
    {
        
        protected:

        public:
        
        static void save(std::vector<Environment*>, Player*, std::string);
    };
}