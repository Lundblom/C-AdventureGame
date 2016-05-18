#include <iostream>

#include "Actor.h"
#include "Player.h"
#include "Wizard.h"
#include "Spell.h"


const int labgame::Wizard::STARTING_HP = 13;
const int labgame::Wizard::STARTING_MP = 50;
const int labgame::Wizard::DEFAULT_INTELLIGENCE = 14;
const int labgame::Wizard::DEFAULT_STRENGTH = 8;

labgame::Wizard::Wizard(std::string name, int hp) : Player(name, hp)
{
    Spell fireball([] (Actor* t) {t->take_damage(8, "fireball");}, "Fireball", 7);
    spell_map["fireball"] = &fireball;
    
    this->strength =  DEFAULT_STRENGTH;
    this->intelligence = DEFAULT_INTELLIGENCE;
}

void labgame::Wizard::cast_spell(Actor* target)
{
    while(true)
    {
        int counter = 1;
        
        for (typename std::map<std::string, Spell*>::iterator 
            it=spell_map.begin(); it!=spell_map.end(); ++it)
        {
            std::string theName =  it->second->name();
            theName[0] = toupper(theName[0]);
            std::cout << counter << ". " << theName << "(" << it->second->cost() <<" mp)" << std::endl;
            counter++;
        }
        std::cout << "Choose one (enter the name): ";
        
        std::string choice;
        std::cin >> choice;
        
        std::cout << std::endl;
        
        auto chosenSpell = spell_map.find(choice);
        
        if(chosenSpell == spell_map.end())
        {
            std::cout << "Not a valid spell!" << std::endl;
            continue;
        }
        
        use_ability(spell_map.find(choice)->second->get_spell(), target);
        break;
    }
}



void labgame::Wizard::fight(Actor* a)
{
    Player::fight(a);
    if(!command_successful)
        return;
    
    start:
    std::cout << "1. Melee attack" << std::endl;
    std::cout << "2. Cast a spell" << std::endl;
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
    
    switch(choice)
    {
        case 1:
            melee_attack(a);
            break;
        case 2:
            cast_spell(a);
            break;
        default:
            std::cout << "Not a valid option" << std::endl;
            goto start; //Please dont kill me
            
    }
    
    std::cin.clear();
    std::cin.ignore(256,'\n');
}

std::string labgame::Wizard::type() const
{
    return "Wizard";
}