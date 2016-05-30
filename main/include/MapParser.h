#include <string>
#include <vector>
#include <queue>

#include "Token.h"
#pragma once
namespace labgame
{
    class MapParser
    {
        private:
        
        int lineCounter = 0;
        std::string filename;
        std::queue<Token> tokens;
        std::size_t find_parenthesis_end(const std::string& s);
        std::string stringtok(const std::string&, char);
        bool is_number(const std::string&) const;
        void parse_arguments(std::string&);
        
        public:
        MapParser(const std::string&);
        
        void tokenize();
        void parse(std::string&);
        
        void debugPrint();
       

    };
}