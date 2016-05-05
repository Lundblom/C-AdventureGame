#include <iostream>
#include <sstream>
#include "Actor.h"
#include "Player.h"
#include "global.h"


void labgame::Player::die()
{
    std::cout << "GAME OVER!" << std::endl;
    std::exit(0);
}

template<class F, class... Args>
void labgame::Player::add_to_map(std::string name, F f, Args&&... args)
{
    command_map[name] = std::bind(f, this, std::ref(args)...);
}

void labgame::Player::help()
{
    std::cout << "---Commands---" << std::endl;
    
    print_map_options(command_map);
    
    command_successful = false;
}

//Add any options the player can do here.
void labgame::Player::populate_map()
{
    add_to_map("fight", &Player::fight, actor_target);
    add_to_map("hp", &Player::hp);
    add_to_map("help", &Player::help);
    add_to_map("inspect", &Player::inspect);
    add_to_map("go", &Player::go, string_target);
}

labgame::Player::Player(std::string name, int hp, Environment* start_position) : Actor(hp, start_position)
{
    this->_name = name;
    populate_map();
}

void labgame::Player::fight(Actor* a)
{
    std::cout << "in player fight with " << a << std::endl;
    if(a == nullptr)
    {
        command_successful = false;
        return;
    }
    std::cout << "You fight " << a->type() << std::endl;
    std::cout << "--You have these options--" << std::endl;
    
    
}

template<typename S>
void labgame::Player::print_map_options(std::map<std::string, S> m)
{
    int counter = 1;
    
    for (typename std::map<std::string, S>::iterator 
        it=m.begin(); it!=m.end(); ++it)
    {
        std::string theName =  it->first;
        theName[0] = toupper(theName[0]);
        std::cout << counter << ". " << theName << std::endl;
        counter++;
    }
}

void labgame::Player::talk_to(Actor * a)
{
    //Do something nice
}

void labgame::Player::go(std::string * t)
{
    labgame::Actor::go(*t);
}

void labgame::Player::inspect()
{
    std::cout << current_location->description() << std::endl;
    std::cout << "--Available Directions--" << std::endl;
    std::vector<std::string> dirs = current_location->directions();
    
    for(std::vector<std::string>::iterator it = dirs.begin();
        it != dirs.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    
    //Used to allow player to enter another command this turn
    command_successful = false;
}

void labgame::Player::action()
{
    while(true)
    {
        //Is set to false when shit goes wrong or when we need to return
        // after executing a command
        command_successful = true;
        std::cout << ">";
        
        std::string input;
        
        
        std::getline(std::cin, input);
        
        std::string input1 = "";
        std::string input2 = "";
        
        int i = 0;
        char currentChar;
        while((currentChar = input[i]) != ' ' && input[i] != '\0')
        {
            input1 += currentChar;
            i++;
        }
        while(input[i] == ' '){i++;}
        while((currentChar = input[i]) != ' ' && input[i] != '\0')
        {
            input2 += currentChar;
            i++;
        }
            
        std::cout << "input1: " << input1 << std::endl;
        std::cout << "input2: " << input2 << std::endl;
            
        auto it1 = command_map.find(input1);
        if(it1 == command_map.end())
        {
            std::cout << "Couldn't find command" << std::endl;
            continue;
        }
        
        
            
        if(input2 != "")
        {
            actor_target = global::get_actor(input2);
            string_target = &input2;
        }
        
        //Executes the selected function
        it1->second();
        if(!command_successful)
            continue;
        break;
    }
    
    
    
}