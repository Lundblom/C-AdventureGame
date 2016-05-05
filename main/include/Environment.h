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
        std::vector<Object> objects;
        std::vector<Environment* > neighbours;
        std::vector<Actor* > visitors;
        std::map<std::string, int> direction_translation;
        
        protected:
        int max_neighbours = 0;
        const int id;
        
        
        
        public:
        Environment(int);
        void add_neighbour(std::string, Environment*);
        
        /**
         * Returns a space-separated string with directions
         **/
        std::vector<std::string> directions() const;
        Environment* neighbour(std::string) const;
        
        std::vector<Actor* > get_visitors() const;
        inline int get_id() const {return id;}
        
        template <typename T>
        Actor* get_first_visitor_of_type()
        {
            for(std::vector<Actor* >::iterator it = visitors.begin(); it != visitors.end(); ++it) 
            {
                if(typeid(T).name() == typeid(*it).name())
                {
                    return (*it);
                }
            }
            return nullptr;
        }
        
        
        virtual std::string description() const = 0;

        virtual void enter(Actor*);
        virtual void leave(Actor*);
        virtual void pick_up(int);
        void drop(Object&);
        
    };
}