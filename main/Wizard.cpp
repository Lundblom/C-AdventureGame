#include <iostream>
#include <algorithm>

#include "Actor.h"
#include "Player.h"
#include "Wizard.h"
#include "Spell.h"


const int labgame::Wizard::STARTING_HP = 13;
const int labgame::Wizard::STARTING_MP = 50;
const int labgame::Wizard::DEFAULT_INTELLIGENCE = 14;
const int labgame::Wizard::DEFAULT_STRENGTH = 8;

const std::map<std::string, labgame::Spell> labgame::Wizard::all_spells = {
    {"fireball", Spell([] (Actor* t) {t->take_damage(9, "fireball");}, "Fireball", 6)},
    {"arcane bolt", Spell([] (Actor* t) {t->take_damage(3, " arcane bolt");}, "Arcane Bolt", 1)}
};


labgame::Wizard::Wizard(std::string name, int hp) : Player(name, hp)
{
    known_spells.push_back("fireball");
    known_spells.push_back("arcane bolt");
    
    this->strength =  DEFAULT_STRENGTH;
    this->intelligence = DEFAULT_INTELLIGENCE;
}

void labgame::Wizard::cast_spell(Actor* target)
{
    while(true)
    {
        int counter = 1;
        
        for(std::vector<std::string>::const_iterator it = known_spells.begin();
            it != known_spells.end(); ++it)
        {
            const Spell * theSpell = &(all_spells.find(*it)->second);
            std::string theName =  theSpell->name();
            theName[0] = toupper(theName[0]);
            std::cout << counter << ". " << theName << "(" << theSpell->cost() <<" mp)" << std::endl;
            counter++;
        }
        std::cout << "Choose one (enter the name): ";
        
        std::string choice;
        std::cin >> choice;
        
        std::cout << std::endl;
        
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        
        auto chosenSpell = all_spells.find(choice);
        
        if(chosenSpell == all_spells.end())
        {
            std::cout << "Not a valid spell!" << std::endl;
            continue;
        }
        
        std::cout << "You cast " << chosenSpell->second.name() << "!" << std::endl;
        
        use_ability(all_spells.find(choice)->second.get_spell(), target);
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