#include <string>
#include <iostream>
#pragma once
namespace labgame
{
    class Token
    {
        public:
        enum TOKENTYPE 
        {
            SPECIFIER,
            NEWLINE,
            INT,
            STRING,
            ARRAY_START,
            ARRAY_END,
        };
        
        private:
        
        TOKENTYPE type;
        std::string data;
        int line;
        
        
        
        public:
        
        Token(TOKENTYPE, std::string, int);
        Token(TOKENTYPE, std::string, int, bool);
        
        int get_type() const;
        int get_line() const;
        
        int get_data_as_int() const;
        std::string get_data_as_string() const;
        friend std::ostream& operator<<(std::ostream&, const Token& t);
    };
    
    
}