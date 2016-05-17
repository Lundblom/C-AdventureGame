#pragma once
#include <vector>
#include <map>
#include "Actor.h"
#include "Object.h"
namespace labgame
{
    class Actor;
    class Environment
    {
        private:
        
        std::vector<Object* > objects;
        std::vector<Environment* > neighbours;
        std::vector<Actor* > visitors;
        std::map<std::string, std::pair<int, std::string>> direction_translation;
        std::map<std::string, int> object_translation;
        
        protected:
        int max_neighbours = 0;
        const int id;
        
        void link(std::string, std::string, Environment *);
        
        public:
        
        Environment(int);
        void add_neighbour(std::string,std::string, Environment*, bool);
        
        std::vector<std::string> directions() const;
        Environment* neighbour(std::string) const;
        std::pair<Environment*, std::string> get_neighbour_and_out(std::string d) const;
        
        std::vector<Actor* > get_visitors() const;
        inline int get_id() const {return id;}
        Object* get_item(std::string name);
        std::string get_items_as_text() const;
        
        template <typename T>
        Actor* get_first_visitor_of_type()
        {
            for(std::vector<Actor* >::iterator it = visitors.begin(); 
                it != visitors.end(); ++it) 
            {
                if(typeid(T).name() == typeid(*it).name())
                {
                    return (*it);
                }
            }
            return nullptr;
        }
        
        void add_item(Object *);
        
        virtual std::string description() const = 0;

        bool can_enter (Actor*, std::string);
        bool can_leave (Actor*, std::string);
        
        virtual void enter(Actor*);
        virtual void leave(Actor*);
        virtual void pick_up(std::string);
        void drop(Object&);
        
    };
}