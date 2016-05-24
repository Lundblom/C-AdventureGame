#include <iostream>
#include <sstream>
#include <algorithm>
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
    add_to_map("help", &Player::help);
    add_to_map("inspect", &Player::inspect);
    add_to_map("go", &Player::go_p, string_target);
    add_to_map("pickup", &Player::pick_up_p, string_target);
    add_to_map("inventory", &Player::display_inventory);
    add_to_map("use", &Player::use_item_p);
    add_to_map("unlock", &Player::unlock_p, string_target);
    add_to_map("drop", &Player::drop_p, string_target);
}

labgame::Player::Player(std::string name, int hp) : Actor(hp)
{
    this->_name = name;
    populate_map();
}

void labgame::Player::fight(Actor* a)
{
    if(a == nullptr || !current_location->contains_actor(a))
    {
        std::cout << "Can't find fight target" << std::endl;
        command_successful = false;
        return;
    }
    std::cout << "You fight " << a->type() << std::endl;
    std::cout << "--You have these options--" << std::endl;
}

void labgame::Player::use_item_p()
{
    if(inventory.size() < 1)
    {
        std::cout << "Inventory is empty" << std::endl;
        command_successful = false;
        return;
    }
    display_inventory();
    
    std::cout << "Enter an item id(1 to " << inventory.size() << "): ";
    
    int input;
    std::cin >> input;
    
    while(std::cin.fail() || input < 1 || input > max_inventory_size())
    {
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout << "Not a valid option" << std::endl;
        std::cout << "Enter an item id: ";
        std::cin >> input;
        std::cout << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(256,'\n');
    
    std::cout << std::endl;
    
    if(input > inventory.size())
    {
        std::cout << "No item in this slot." << std::endl;
        command_successful = false;
        return;
    }
    
    if(is_equippable(input-1))
    {
        Actor::equip(input-1);
    }
    else
    {
        Actor::use_item(input-1);
    }
}

template<typename S>
void labgame::Player::print_map_options(std::map<std::string, S> m)
{
    for (typename std::map<std::string, S>::iterator 
        it=m.begin(); it!=m.end(); ++it)
    {
        std::string theName =  it->first;
        theName[0] = toupper(theName[0]);
        std::cout << theName << std::endl;
    }
}

void labgame::Player::talk_to(Actor * a)
{
    if(a == nullptr)
    {
        command_successful = false;
        return;
    }
}

std::string labgame::Player::comparable_type() const
{
    return "Player";
}

void labgame::Player::add_alias(std::string alias, std::string command)
{
    alias_map.insert(std::pair<std::string,std::string>(alias,command));
}

void labgame::Player::go_p(std::string * t)
{
    if(t == nullptr)
    {
        command_successful = false;
        return;
    }
    labgame::Actor::go(*t);
}

void labgame::Player::drop_p(std::string * s)
{
    if(s == nullptr)
    {
        command_successful = false;
        return;
    }
    drop(*s);
}

void labgame::Player::pick_up_p(std::string * s)
{
    if(s == nullptr)
    {
        command_successful = false;
        return;
    }
    Player::pick_up(*s);
}

void labgame::Player::unlock_p(std::string* s)
{
    if(s == nullptr)
    {
        command_successful = false;
        return;
    }
    std::cout << "IN  P unlock" << std::endl;
    Player::unlock(*s);
}

void labgame::Player::display_inventory() const
{
    std::cout << std::endl;
    if(inventory.size() == 0)
    {
        std::cout << "Inventory is empty" << std::endl;
    }
    else
    {
        int counter = 1;
        std::cout << "---Inventory---" << std::endl;
        for (auto i = inventory.begin(); i != inventory.end(); ++i) 
        {
            std::string star;
            if(*i == weapon or *i == armor or *i == hat or *i == boots or *i == extra)
            {
                star = " *";
            }
            std::cout << counter++ << ". " << (*i)->Name() << star << std::endl;
        }
    }
    std::cout << std::endl;
}

bool labgame::Player::pick_up(std::string s)
{
    bool success = Actor::pick_up(s);
    
    if(!success)
    {
        command_successful = false;
    }
    if(success)
    {
        //New item is pushed back
        std::cout << "You picked up " << inventory[inventory.size() - 1]->Name() << std::endl; 
    }
    else if(inventory_is_full())
    {
        std::cout << "Your inventory is full." << std::endl;
    }
    else
    {
        std::cout << "Can't find item." << std::endl;
    }
}

void labgame::Player::inspect()
{
    std::cout << current_location->description() << std::endl << std::endl;
    std::cout << "--Available Directions--" << std::endl;
    std::vector<std::string> dirs = current_location->directions();
    
    for(std::vector<std::string>::iterator it = dirs.begin();
        it != dirs.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "--Items in room--" << std::endl;
    std::cout << current_location->get_items_as_text() << std::endl;
    std::cout << std::endl;
    
    std::vector<std::string> visitors = current_location->get_visitor_names();
    std::cout << "--Creatures in room--" << std::endl;
    for (std::vector<std::string>::const_iterator i = visitors.begin(); 
        i != visitors.end(); ++i) 
    {
        if(*i == full_name())
        {
            std::cout << "You" << std::endl;
        }
        else
        {
            std::cout << *i << std::endl;
        }
    }
    //Used to allow player to enter another command this turn
    command_successful = false;
}

void labgame::Player::action()
{
    std::cout << "Your turn!" << std::endl;
    
    start:
    while(true)
    {
        //Is set to false when shit goes wrong or when we need to return
        //after executing a command
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
        while((currentChar = input[i]) != '\0')
        {
            input2 += currentChar;
            i++;
        }
        
        std::transform(input1.begin(), input1.end(), input1.begin(), ::tolower);
        
            
        auto it1 = command_map.find(input1);
        if(it1 == command_map.end())
        {
            //Also check for any aliases
            auto it2 = alias_map.find(input1);
            if(it2 == alias_map.end())
            {
                std::cout << "Couldn't find command" << std::endl;
                continue;
            }
            else
            {
                it1 = command_map.find(it2->second);
                
                if(it1 == command_map.end())
                {
                    //This means there's an invalid alias
                    std::cout << "Couldn't find command" << std::endl;
                    goto start;
                }
            }
        }
        
        
            
        if(input2 != "")
        {
            actor_target = global::get_actor(input2);
            string_target = &input2;
        }
        
        //Executes the selected function
        it1->second();
        
        actor_target = nullptr;
        string_target = nullptr;
        
        if(!command_successful)
        {
            continue;
        }
        break;
    }
}