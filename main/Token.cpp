#include <string>
#include <iostream>

#include "Token.h"
 

namespace labgame
{
    
    Token::Token(Token::TOKENTYPE t, std::string _data) : type(t), data(_data)
    {
        
    }
    
    int Token::get_data_as_int() const
    {
        return stoi(data);
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
        os << "Token: " << &dt << "Type: " << dt.get_type() << " Data: " << 
            dt.get_data_as_string() << std::endl;
        return os;
    }
}