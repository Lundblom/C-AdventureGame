#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <map>
#include <vector>
#include "PositionVector.h"
#include "global.h"
#include "Actor.h"
#include "NPC.h"
#include "Troll.h"
#include "Wizard.h"
#include "Environment.h"
#include "Room.h"
#include "Forest.h"
#include "Weapon.h"
#include "LockedRoom.h"
#include "Weather.h"
#include "MapParser.h"



//Global command map
std::vector<labgame::Environment*> world;


using namespace labgame; 


void loadAliases(std::string filename, Player * p)
{
    std::ifstream file("aliases");
    std::string str; 
    while (std::getline(file, str))
    {
        std::istringstream iss(str);
        
        std::string alias;
        std::string command;
        
        if(iss)
        {
            iss >> alias;
        }
        else
        {
            throw std::runtime_error("Alias file is not according to syntax: [alias] [command].");
        }
        if(iss)
        {
            iss >> command;
        }
        else
        {
            throw std::runtime_error("Alias file is not according to syntax: [alias] [command].");
        }
        
        if(command == "" or alias == "")
        {
            throw std::runtime_error("Alias file is not according to syntax: [alias] [command].");
        }
        
        p->add_alias(alias, command);
    }
}

int main() {
    
    //initiate random 
    std::srand(time(NULL));
    
    Player* player;
    
    //TEST
    MapParser mp("in", &world, player);
    mp.tokenize();
    mp.evaluate();
    
    int player_start = mp.get_player_start();
    
    int chosenClass; //use ENUM for this later
    std::string name;

    //LABEL
    chooseClass:
    
    std::cout << "Choose your class" << std::endl;
    std::cout << "1. Wizard" << std::endl;
    std::cout << "Choose one: ";
    
    int choice;
    std::cin >> choice;
    std::cout << std::endl;
    
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout << "Not a valid option" << std::endl;
        std::cout << "Choose one: ";
        std::cin >> choice;
        std::cout << std::endl;
    }
    
    if(choice < 1 || choice > 1 )
    {
        goto chooseClass;
    }
    
    chosenClass = choice;
    
    std::cout << "Enter your name: ";
    std::cin >> name;
    
    
    switch(chosenClass)
    {
        case 1:
            player = new Wizard(name, Wizard::STARTING_HP);
            player->move_to(world[player_start]);
            break;
    }
    
    loadAliases("aliases", player);
    
    //CLEAR ALL INPUT
    std::cin.clear();
    std::cin.ignore(256,'\n');
    
    
    
    /**
     * INITIALIZE ACTORS
     **/
     
    //Troll* troll = new Troll("Sven");
    //troll->move_to(world[3]);
   /**
    * MAIN LOOP
    * 
    **/
   while(true)
   {
       std::clog << "Actor turns" << std::endl;

       global::map_on_actors([] (Actor* a) { a->action();});
       
       player->action();
       
       //Clear any leftover input
       std::cin.clear();
       
       if(global::should_save_be_executed())
       {
           //TODO: ACTUALLY SAVE
           global::has_executed_save();
       }
       if(player->_quit)
       {
           break;
       }
   }
   std::cout << "Trying to delete player" << std::endl;
   delete player;
   
   std::cout << "Trying to delete all rooms" << std::endl;
   for (std::vector<Environment* >::iterator i = world.begin(); 
   i != world.end(); ++i) 
   {
       std::cout << "Trying a room" << std::endl;
      delete (*i); 
   }
   
   std::cout << "Deleting all npcs" << std::endl;
   global::map_on_actors([] (Actor* a) {delete a;});
}
