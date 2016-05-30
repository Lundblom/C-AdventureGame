#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "MapParser.h"
#include "Token.h"

namespace labgame
{
    
    MapParser::MapParser(const std::string& s)
    {
        this-> filename = s;
    }
    
    /*void MapParser::evaluate()
    {
        
    }*/
    
    void MapParser::tokenize()
    {
        std::ifstream f;
        f.open(filename);
        
        
        std::string line;
        while(std::getline(f, line))
        {
            if(line == "")
            {
                continue;
            }
            parse(line);
            lineCounter = 0;
        }
        
    }
    
    void MapParser::parse(std::string& line)
    {
        std::string n = stringtok(line, ':');
        tokens.push(Token(Token::SPECIFIER, n));
        parse_arguments(line);
        tokens.push(Token(Token::NEWLINE, "\n"));
    }
    
    void MapParser::parse_arguments(std::string& line)
    {
        std::string t;
        while( !(t = stringtok(line, ',')).empty())
        {
            if(is_number(t))
            {
                tokens.push(Token(Token::INT, t));
            }
            else if(t.at(0) == '[') 
            {
                int currentCounter = lineCounter;
                
                //The line from where the '[' is
                std::string currentLine = std::string(line, 
                    lineCounter - t.length() - 1);
                    
                std::size_t endPos = find_parenthesis_end(currentLine);
                if(endPos == -1)
                {
                    std::cout << "Invalid array in input map file, can't continue." << std::endl;
                    exit(1);
                }
                tokens.push(Token(Token::ARRAY_START, "["));

                std::size_t startPos = currentCounter - t.length() - 1;
                
                //Create a string of all arguments
                //Removes the []
                std::string arguments(line, startPos + 1, endPos - 1);
                
                //Recursively handle the array
                //Have to cache and reset lineCounter when going recursive
                int temp = lineCounter;
                lineCounter = 0;
                
                parse_arguments(arguments);
                
                //Set linecounter to after the entire parenthesis
                lineCounter = temp - t.length() + arguments.length() + 1;
                
                //Jumps over the comma after the array.
                //Avoids out of range errors by checking bounds if 
                //we are at the end of the line.
                if(lineCounter != line.length() && line.at(lineCounter) == ',')
                {
                    ++lineCounter;
                }
                
                tokens.push(Token(Token::ARRAY_END, "]"));
            }
            else
            {
                tokens.push(Token(Token::STRING, t));
            }
        }
    }
    
    bool MapParser::is_number(const std::string& s) const
    {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    }
    
    std::size_t MapParser::find_parenthesis_end(const std::string& s)
    {
        int left_found = 0;
        int position_counter = 0;
        int ret = -1;
        for(std::string::const_iterator i = s.begin();
            i != s.end(); ++i)
        {
            if(*i == '[')
            {
                ++left_found;
            }
            else if(*i == ']' && left_found > 1)
            {
                --left_found;
            }
            else if(*i == ']'  && left_found == 1)
            {
                ret = position_counter;
                break;
            }
            ++position_counter;
        }
        return ret;
    }
    
    std::string MapParser::stringtok(const std::string& s, char c)
    {
        std::string result;
        
        for(std::string::const_iterator i = s.begin() + this->lineCounter;
            i != s.end(); ++i)
        {
            //Increment index everytime
            //Also skips character c if we find it
            ++this->lineCounter;
            if((*i) == c)
            {
                break;
            }
            result += *i;
        }
        return result;
    }
    
    void MapParser::debugPrint()
    {
        while(!tokens.empty())
        {
            Token t = tokens.front();
            tokens.pop();
            
            std::cout << t;
            
        }
    }
    
}