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
        
        std::vector<Environment* > neighbours;
        std::vector<Actor* > visitors;
        std::map<std::string, std::pair<int, std::string>> direction_translation;
        std::map<std::string, Object*> objects;
        
        protected:
        int max_neighbours = 0;
        const int id;
        
        void link(std::string, std::string, Environment *);
        
        public:
        
        Environment(int);
        void add_neighbour(std::string,std::string, Environment*, bool);
        
        std::vector<std::string> directions() const;
        Environment* neighbour(std::string) const;
        
        
        std::vector<std::string> get_visitor_names() const;
        inline int get_id() const {return id;}
        Object* get_item(std::string name);
        std::string get_items_as_text() const;
        std::pair<Environment*, std::string> get_neighbour_and_out(std::string d) const;
        Actor* get_first_visitor_of_type(std::string type) const;
        
        bool contains_actor(Actor* a) const;
        
        void add_item(Object *);
        
        virtual std::string description() const = 0;

        virtual bool can_enter (Actor*, std::string);
        virtual bool can_leave (Actor*, std::string);
        
        virtual void enter(Actor*);
        virtual void leave(Actor*);
        virtual void pick_up(std::string);
        void drop(Object*);
        
    };
}