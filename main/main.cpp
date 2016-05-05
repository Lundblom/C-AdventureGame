#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include "PositionVector.h"
#include "Actor.h"
#include "NPC.h"
#include "Troll.h"
#include "Wizard.h"
#include "Environment.h"
#include "Room.h"
#include "Forest.h"



//Global command map

std::map<std::string, labgame::Actor*> actor_map;
std::vector<labgame::Environment*> world;


using namespace labgame; 


int main() {
    
    //initiate random 
    std::srand(time(NULL));
    
    int chosenClass; //use ENUM for this later
    std::string name;
    
    /**
     * INITIALIZE WORLD
     **/
     for(int i = 0; i < 12; i++)
     {
        world.push_back(new Room(i+1));
     }
     
     world.push_back(new Forest(13, "It's filled with bugs. EW!"));
     
    /**
     * CREATE NEIGHBOURS
     **/
     
    world[0]->add_neighbour("se", world[12]);
    world[1]->add_neighbour("e", world[12]);
    world[2]->add_neighbour("n", world[2]);
    world[3]->add_neighbour("e", world[5]);
    world[4]->add_neighbour("sw", world[12]);
    world[5]->add_neighbour("w", world[3]);
    world[5]->add_neighbour("s", world[6]);
    world[6]->add_neighbour("n", world[5]);
    world[7]->add_neighbour("sw", world[8]);
    world[7]->add_neighbour("s", world[9]);
    world[7]->add_neighbour("e", world[11]);
    world[8]->add_neighbour("ne", world[7]);
    world[8]->add_neighbour("w", world[12]);
    world[8]->add_neighbour("se", world[9]);
    world[9]->add_neighbour("nw", world[8]);
    world[9]->add_neighbour("n", world[7]);
    world[9]->add_neighbour("se", world[10]);
    world[10]->add_neighbour("nw", world[9]);
    world[11]->add_neighbour("w", world[7]);
    world[11]->add_neighbour("sw", world[9]);
    world[12]->add_neighbour("nw", world[0]);
    world[12]->add_neighbour("ne", world[4]);
    world[12]->add_neighbour("w", world[1]);
    world[12]->add_neighbour("s", world[5]);
    world[12]->add_neighbour("e", world[8]);
    
    Player* player;
    
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
            player = new Wizard(name, world[1]);
            break;
    }
    
    //CLEAR ALL INPUT
    std::cin.clear();
    std::cin.ignore(256,'\n');
    
    
    
    /**
     * INITIALIZE ACTORS
     **/
     
     Troll troll("Sven", world[7]);
   
   //command_map["fight"]();
   /**
    * MAIN LOOP
    * 
    **/
   while(true)
   {
       std::cout << "Your turn!" << std::endl;
       player->action();
       
       //Clear any leftover input
       std::cin.clear();
       std::cin.ignore(256,'\n');
       
       std::cout << "Processing enemy turns..." << std::endl;
       for (std::map<std::string, labgame::Actor*>::iterator 
        it=actor_map.begin(); it!=actor_map.end(); ++it)
       {
           it->second->action();
       }
   }
   
   free(player);
}
