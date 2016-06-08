#include <iostream>
#include <sstream>
#include <algorithm>
#include "Actor.h"
#include "Player.h"
#include "global.h"


void labgame::Player::die()
{
    std::cout << "GAME OVER!" << std::endl;
    quit();
}

template<class F, class... Args>
void labgame::Player::add_to_map(std::string name, F f, Args&&... args)
{
    command_map[name] = std::bind(f, this, std::cref(args)...);
}

void labgame::Player::help()
{
    std::cout << "---Commands---" << std::endl;
    
    print_map_options(command_map);
    
    command_successful = false;
}

void labgame::Player::equip(std::string s)
{
    Object * i = find_item_in_inventory(s);
    
    if(Backpack * b = dynamic_cast<Backpack*>(i))
    {
        this->backpack = b;
        return;
    }
    Actor::equip(s);
}

void labgame::Player::unequip(std::string s)
{
    Object * i = find_item_in_inventory(s);
    command_successful = false;
    
    if(i == backpack)
    {
        backpack = nullptr;
        return;
    }
    Actor::unequip(s);
}

//Add any options the player can do here.
void labgame::Player::populate_map()
{
    add_to_map("fight", &Player::fight, actor_target);
    add_to_map("help", &Player::help);
    add_to_map("inspect", &Player::inspect);
    add_to_map("go", &Player::go, string_target);
    add_to_map("pickup", &Player::pick_up, string_target);
    add_to_map("inventory", &Player::display_inventory);
    add_to_map("put", &Player::put_in_container, split1, "");
    add_to_map("remove", &Player::remove_from_container, split1, "");
    add_to_map("use", &Player::use_item, string_target);
    add_to_map("unequip", &Player::unequip, string_target);
    add_to_map("unlock", &Player::unlock, string_target);
    add_to_map("drop", &Player::drop, string_target);
    add_to_map("wait", &Actor::wait);
    add_to_map("save", &Player::save, string_target);
    add_to_map("quit", &Player::quit);
}

labgame::Player::Player(std::string name, int hp) : Actor(hp)
{
    this->_name = name;
    populate_map();
}
void labgame::Player::quit()
{
    _quit = true;
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

void labgame::Player::put_in_container(std::string t, std::string)
{
    if(inventory.size() == 0)
    {
        std::cout << "Inventory is empty" << std::endl;
        return;
    }
    std::cout << "Put what in " << t << "?" << std::endl;
    
    display_inventory();
    
    std::string input;
    std::cout << ">";
    
    std::getline(std::cin, input);
    std::cout << std::endl;
    
    Actor::put_in_container(t, input);
}

void labgame::Player::remove_from_container(std::string t, std::string)
{
    if(inventory.size() == 0)
    {
        std::cout << "Inventory is empty" << std::endl;
        return;
    }
    
    Object * o = find_item_in_inventory(t);
    
    
    if(o == nullptr)
    {
        std::cout << "Cant find " << t << " in inventory" << std::endl;
        return;
    }
    
    Container * c = dynamic_cast<Container*>(o);
    if(c == nullptr)
    {
        std::cout << o->Name() << " is not a container" << std::endl;
        return;
    }
    
    std::cout << "Remove what from " << t << "?" << std::endl;
    
    std::cout << c->get_items_as_text();
    
    std::string input;
    
    std::getline(std::cin, input);
    
    Actor::remove_from_container(t, input);
}

void labgame::Player::use_item(std::string s)
{
    if(inventory.size() < 1)
    {
        std::cout << "Inventory is empty" << std::endl;
        command_successful = false;
        return;
    }
    
    int input = 0;
    
    std::stringstream stream(s);
    
    if ( !(stream >> input) )
    {
        input = 0;
    }
    if(input > inventory.size())
    {
        std::cout << "No item in this slot." << std::endl;
        command_successful = false;
        return;
    }
    
    Object * o = find_item_in_inventory(s);
    
    if(is_equippable(o))
    {
        Player::equip(s);
    }
    else
    {
        Actor::use_item(s);
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

void labgame::Player::save(std::string filename)
{
    if(filename == "")
    {
        std::cout << "No filename specified" << std::endl;
        command_successful = false;
        return;
    }
    global::save(filename);
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
            if(*i == weapon or *i == armor or *i == hat or *i == boots or *i == extra or *i == backpack)
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
            
            //set split values
            std::istringstream iss(input2);
            std::getline(iss, split1, ' ');
            std::getline(iss, split2, ' ');
            
            actor_target = global::get_actor(input2);
            string_target = input2;
        }
        
        //Executes the selected function
        it1->second();
        
        actor_target = nullptr;
        string_target = "";
        
        if(!command_successful)
        {
            continue;
        }
        break;
    }
}