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
    
    int chosenClass; //use ENUM for this later
    std::string name;
    
    /**
     * INITIALIZE WORLD
     **/
     world.push_back(new Room(1));
     world.push_back(new Room(2));
     world.push_back(new Room(3));
     world.push_back(new Forest(4, "It's filled with bugs. EW!"));
     world.push_back(new LockedRoom(5, "It's a room!", {{"s", "Bronze Key"}, {"e", "Bronze Key"}}));
     world.push_back(new Room(6));
     
     /**
      * ADD ITEMS
      **/
    world[0]->add_item(new Object("Bronze Key"));
    world[5]->add_item(new Weapon("Amazing Really Cool Sword!", 10));   
    /**
     * CREATE NEIGHBOURS
     **/
     
    world[0]->add_neighbour("se","nw", world[3], true);
    world[1]->add_neighbour("s","n", world[3], true);
    world[2]->add_neighbour("sw","ne", world[3],true);
    world[2]->add_neighbour("n", "s", world[4], true);
    world[4]->add_neighbour("e", "w", world[5], true);
    
    Player* player;
    
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
            player->move_to(world[1]);
            break;
    }
    
    loadAliases("aliases", player);
    
    //CLEAR ALL INPUT
    std::cin.clear();
    std::cin.ignore(256,'\n');
    
    
    
    /**
     * INITIALIZE ACTORS
     **/
     
    Troll troll("Sven");
    troll.move_to(world[3]);
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
   }
   free(player);
}
