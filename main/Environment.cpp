#include <stdexcept>
#include <typeinfo>
#include <sstream>
#include "Environment.h"
#include "Backpack.h"
#include "MapParser.h"


namespace labgame
{
    Environment::Environment(int _id) : id(_id)
    {
    }
    
    Environment::~Environment()
    {
        for (auto i = objects.begin(); i != objects.end(); ++i) 
        {
            delete i->second;
        }
        
        objects.clear();
        
        neighbours.clear();
        visitors.clear();
        direction_translation.clear();
    }
    
    Environment* Environment::neighbour(std::string d) const
    {
        auto res = direction_translation.find(d);
        if(res == direction_translation.end())
        {
            return nullptr;
        }
        return neighbours.at(res->second.first);
    }
    
    std::pair<Environment*, std::string> Environment::get_neighbour_and_out(std::string d) const
    {
        auto res = direction_translation.find(d);
        if(res == direction_translation.end())
        {
            return {nullptr, ""};
        }
        return {neighbours.at(res->second.first), res->second.second};
    }
    
    void Environment::add_neighbour(std::string directionOut, 
        std::string directionIn, Environment* ePtr, bool dualLink)
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
        
        if(dualLink)
        {
            ePtr->link(directionIn, directionOut, this);
        }
        
        direction_translation[directionOut] = {position, directionIn};
    }
    
    bool Environment::can_enter(Actor* a, std::string dir)
    {
        return true;
    }
    
    void Environment::drop(Object* o)
    {
        o->drop();
        objects.insert({o->Name(), o});
    }
    
    bool Environment::can_leave(Actor* a, std::string dir)
    {
        return true;
    }
    
    void Environment::enter(Actor * a)
    {
        visitors.push_back(a);
    }

    bool Environment::contains_actor(Actor* a) const
    {
        for (std::vector<Actor*>::const_iterator i = visitors.begin();
            i != visitors.end(); ++i) 
        {
            if((*i) == a)
            {
                return true;
            }
        }
        return false;
    }
    
    void Environment::leave(Actor * a)
    {
        for(std::vector<Actor *>::iterator it = visitors.begin(); it != visitors.end(); it++)
        {
            if(*it == a)
            {
                visitors.erase(it);
                return;
            }
        }
    }
    
    std::vector<std::string> Environment::get_visitor_names() const
    {
        std::vector<std::string> result;
        
        for (std::vector<Actor* >::const_iterator i = visitors.begin();
            i != visitors.end(); ++i) 
        {
            result.push_back((*i)->full_name());
        }
        
        return result;
    }
    
    
    void Environment::link(std::string out, std::string in, Environment * e)
    {
        if(neighbours.size() >= max_neighbours)
        {
            std::ostringstream oss;
            oss << "Can't link! "; 
            oss << "Can't create more neighbours in environment with id "; 
            oss << id << ". ";
            oss << "Trying to add id " << e->id << ". ";
            oss << "Max neighbours is " << max_neighbours;
            throw std::out_of_range(oss.str());
        }
        
        neighbours.push_back(e);
        int position = neighbours.size() - 1;
        
        direction_translation[out] = {position, in};
    }
    
    Actor* Environment::get_first_visitor_of_type(std::string type) const
    {
        for(std::vector<Actor* >::const_iterator it = visitors.begin(); 
            it != visitors.end(); ++it) 
        {
            if((*it)->comparable_type() == type)
            {
                return (*it);
            }
        }
        return nullptr;
    }
    
    std::string Environment::get_items_as_text() const
    {
        std::ostringstream os;
        for (std::map<std::string, Object*>::const_iterator i = objects.begin();
        i != objects.end(); ++i) 
        {
            os << i->second->Name() << std::endl;
        }
        return os.str();
    }
    
    Object* Environment::get_item(std::string name)
    {
        auto it = objects.find(name);
        
        if(it == objects.end())
        {
            return nullptr;
        }
        return it->second;
    }
    
    std::string Environment::get_actors_as_serializable() const
    {
        std::string result = "";
        for (auto i = visitors.begin(); i != visitors.end(); ++i) 
        {
            result += (*i)->get_as_serializable();
            result += "\n";
        }
        return result;
    }
    
    std::string Environment::get_objects_as_serializable() const
    {
        std::string result;
        for (auto i = objects.begin(); i != objects.end(); ++i) 
        {
            result += (*i).second->get_as_serializable(std::to_string(get_id()));
        }
        for (auto i = visitors.begin(); i != visitors.end(); ++i) 
        {
            result += (*i)->get_inventory_as_serializable();
        }
        return result;
    }
    
    std::string Environment::get_links_as_serializable() const
    {
        std::string result = MapParser::ONE_WAY_NAME;
        
        result += MapParser::SPECIFIER_DELIMETER;
        result += std::to_string(get_id());
        result += MapParser::DELIMETER;
        result += MapParser::ARRAY_START;
        
        bool first = true;;
        for (auto i = direction_translation.begin(); i != direction_translation.end(); ++i) 
        {
            if(first)
            {
                first = false;
            }
            else
            {
                result += MapParser::DELIMETER;
            }
            std::string forwardDir = i->first;
            std::string targetId = std::to_string(neighbour(forwardDir)->get_id());
            
            result += MapParser::ARRAY_START;
            result += forwardDir;
            result += MapParser::DELIMETER;
            result += targetId;
            result += MapParser::ARRAY_END;

        }
        
        result += MapParser::ARRAY_END;
        
        return result;
    }

    void Environment::add_item(Object * o)
    {
        objects.insert({o->Name(), o});
    }
    
    std::vector<std::string> Environment::directions() const
    {
        std::vector<std::string> dirs;
        dirs.reserve(this->direction_translation.size());
        int i = 0;
        for (std::map<std::string, std::pair<int, std::string>>::const_iterator 
        it=direction_translation.begin(); it!=direction_translation.end(); ++it)
        {
            dirs.push_back(it->first);
        }
        return dirs;
    }
    
    void Environment::pick_up(std::string name)
    {
        objects.erase(name);
    }
}