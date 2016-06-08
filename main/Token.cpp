#include <string>
#include <iostream>
#include <algorithm>

#include "Token.h"
 

namespace labgame
{
    
    Token::Token(Token::TOKENTYPE t, std::string _data, int _line) 
        : type(t), line(_line)
    {
        std::transform(_data.begin(), _data.end(), _data.begin(), ::tolower);
        data = _data;
    }
    
    Token::Token(Token::TOKENTYPE t, std::string _data, int _line, bool _tolower) 
        : type(t), line(_line)
    {
        if(_tolower)
        {
            std::transform(_data.begin(), _data.end(), _data.begin(), ::tolower);
        }
        data = _data;
    }
    
    int Token::get_data_as_int() const
    {
        return stoi(data);
    }
    
    int Token::get_line() const
    {
        return line;
    }
    
    std::string Token::get_data_as_string() const
    {
        return data;
    }
    
    int Token::get_type() const
    {
        return type;
    }
    
    std::ostream& operator<<(std::ostream& os, const Token& dt)
    {
        os << "Token - " << "Type: " << dt.get_type() << " Data: " << 
            dt.get_data_as_string() << "Line: " << dt.get_line();
        return os;
    }
}