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
#include "MapSaver.h"



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
    
    std::cout << "\033[1;33mWELCOME TO A DUNGEON CRAWLER\033[0m\n\n";
    
    std::vector<labgame::Environment*> world;
    std::string modeChoice;
    Player* player = nullptr;
    int chosenClass; //use ENUM for this later
    std::string name;
    
    while(true)
    {
        std::cout << "Would you like to \033[32mload\033[0m a game or start a \033[32mnew\033[0m one?" << std::endl;
        
        std::getline(std::cin, modeChoice);
        
        if(modeChoice == "new" || modeChoice == "load")
        {
            break;
        }
    }
    
    MapParser mp;
    
    if(modeChoice == "new")
    {
        MapParser mp("in", &world, &player);
        mp.tokenize();
        mp.evaluate();
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
                player->move_to(world[mp.get_player_start()]);
                break;
        }
        
        
    }
    else if(modeChoice == "load")
    {
        std::string worldname;
        std::cout << "Enter the name of your savefile: ";
        std::getline(std::cin, worldname);
        std::cout << std::endl;
        std::cout << "Loading world..." << std::endl;
        MapParser mp(worldname, &world, &player);
        mp.tokenize();
        mp.evaluate();
    }
    
    
    
    loadAliases("aliases", player);
    
    //CLEAR ALL INPUT
    std::cin.clear();
   /**
    * MAIN LOOP
    * 
    **/
   while(true)
   {
       global::map_on_actors([] (Actor* a) { a->action();});
       
       playerTurn:
       player->action();
       
       //Clear any leftover input
       std::cin.clear();
       
       if(global::should_save_be_executed())
       {
           MapSaver::save(world,player, global::save_filename());
           global::has_executed_save();
           goto playerTurn;
       }
       if(player->_quit)
       {
           break;
       }
   }
   
   delete player;
   for (std::vector<Environment* >::iterator i = world.begin(); 
   i != world.end(); ++i) 
   {
      delete (*i); 
   }
   global::map_on_actors([] (Actor* a) {delete a;});
}
