#include <iostream>
#include <fstream>
#include "MapSaver.h"
#include "MapParser.h"

namespace labgame
{
    void MapSaver::save(std::vector<Environment*> world, Player* player, std::string filename)
    {
        std::string room_string;
        std::string link_string;
        std::string npc_string;
        std::string item_string;
        std::string player_location;
        
        int counter = 0;
        
        for (auto i = world.begin(); i != world.end() && (*i) != nullptr; ++i) 
        {
            room_string += (*i)->get_as_serializable();
            room_string += "\n";
            link_string += (*i)->get_links_as_serializable();
            link_string += "\n";
            npc_string += (*i)->get_actors_as_serializable();
            item_string += (*i)->get_objects_as_serializable();
            item_string += "\n";
        }
        
        player_location += MapParser::PLAYER_START;
        player_location += MapParser::SPECIFIER_DELIMETER;
        player_location += std::to_string(player->get_location()->get_id());

        std::ofstream f;
        f.open(filename);
        f << room_string;
        f << link_string;
        f << npc_string;
        f << item_string;
        f << player_location;
        f.close();
    }
}