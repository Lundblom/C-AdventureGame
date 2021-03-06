#include "LockedRoom.h"
#include "MapParser.h"

namespace labgame
{
    LockedRoom::LockedRoom(int _id, std::string _desc,
        std::vector<std::pair<std::string, std::string>> l) : 
        IndoorEnvironment(_id), room_description(_desc)
    {
        max_neighbours = NEIGHBOURS;
        for (std::vector<std::pair<std::string, std::string>>
            ::const_iterator i = l.begin(); i != l.end(); ++i) 
        {
            locked_directions.push_back((*i).first);
            required_items.insert(*i);
        }
    }
    
    LockedRoom::~LockedRoom()
    {
        locked_directions.clear();
        required_items.clear();
    }
    
    void LockedRoom::wait(Actor* a) 
    {
        
    }
    
    std::string LockedRoom::get_as_serializable() const
    {
        std::string result;
        
        result += MapParser::LOCKEDROOM_NAME;
        result += MapParser::SPECIFIER_DELIMETER;
        result += get_id();
        result += MapParser::DELIMETER;
        result += MapParser::ARRAY_START;
        for (auto i = locked_directions.begin(); i != locked_directions.end(); ++i) 
        {
            auto j = required_items.find(*i);
            if(j != required_items.end())
            {
                result += MapParser::ARRAY_START;
                result += j->first;
                result += MapParser::DELIMETER;
                result += j->second;
                result += MapParser::ARRAY_END;
            }
        }
        result += MapParser::ARRAY_END;
        
        return result;
    }
    
    bool LockedRoom::unlock(Actor* a, std::string dir)
    {
        std::cout << "In LockedRoom unlock with dir " << dir << std::endl;
        std::cout << "Required items size: " << required_items.size() << std::endl;
        if(required_items.find(dir) == required_items.end())
        {
            return false;
        }
        std::cout << "Found: " << required_items.find(dir)->first << std::endl;
        std::string itemName = required_items.find(dir)->second;
        std::cout << "Itemname: " << itemName << std::endl;
        if(a->has_item(itemName))
        {
            std::cout << "it has the item " << std::endl;
            for (std::vector<std::string>::iterator 
                i = locked_directions.begin(); i != locked_directions.end(); ++i) 
            {
                if(*i == dir)
                {
                    std::cout << "Removing direction " << std::endl;
                    locked_directions.erase(i);
                    return true;
                }
            }
            //If we get here the door is already unlocked
            return true;
        }
        return false;
    }
    
    bool LockedRoom::is_locked(std::string dir) const
    {
        for (std::vector<std::string>::const_iterator i 
            = locked_directions.begin(); i != locked_directions.end(); ++i) 
        {
            if(*i == dir)
            {
                return true;
            }
        }
        return false;
    }
    
    std::string LockedRoom::description() const
    {
        std::string ret = "This is a room. ";
        ret += room_description;
        return ret;
    }
    
    bool LockedRoom::can_enter(Actor* a, std::string dir)
    {
        return !is_locked(dir);
    }
    
    bool LockedRoom::can_leave(Actor* a, std::string dir)
    {
        return !is_locked(dir);
    }
}