#include <stdexcept>
#include <typeinfo>
#include <sstream>
#include "Environment.h"


namespace labgame
{
    Environment::Environment(int _id) : id(_id)
    {
    }
    
    Environment* Environment::neighbour(std::string d) const
    {
        auto res = direction_translation.find(d);
        if(res == direction_translation.end())
        {
            return nullptr;
        }
        return neighbours.at(res->second);
    }
    
    void Environment::add_neighbour(std::string direction, Environment* ePtr)
    {
        if(neighbours.size() >= max_neighbours)
        {
            std::ostringstream oss;
            oss << "Can't create more neighbours in environment with id "; 
            oss << id << ". ";
            oss << "Trying to add id " << ePtr->id << ". ";
            oss << "Max neighbours is " << max_neighbours;
            throw std::out_of_range(oss.str());
        }
        
        neighbours.push_back(ePtr);
        int position = neighbours.size() - 1;
        
        direction_translation[direction] = position;
    }
    
    
    void Environment::enter(Actor * a)
    {
        visitors.push_back(a);
    }
    
    void Environment::leave(Actor * a)
    {
        for(std::vector<Actor *>::iterator it = visitors.begin(); it != visitors.end(); it++)
        {
            if(*it == a)
            {
                visitors.erase(it);
            }
        }
    }
    
    std::vector<std::string> Environment::directions() const
    {
        std::vector<std::string> dirs(this->direction_translation.size());
        int i = 0;
        for (std::map<std::string, int>::const_iterator 
        it=direction_translation.begin(); it!=direction_translation.end(); ++it)
        {
            dirs.push_back(it->first);
        }
        return dirs;
    }
    
    void Environment::pick_up(int index)
    {
        //Do something
    }
}