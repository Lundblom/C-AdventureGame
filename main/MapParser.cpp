#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "MapParser.h"
#include "Token.h"
#include "Player.h"
#include "Environment.h"
#include "Forest.h"
#include "Room.h"
#include "LockedRoom.h"
#include "Troll.h"

namespace labgame
{
    
    const std::string MapParser::FOREST_NAME = "forest";
    const std::string MapParser::ROOM_NAME = "room";
    const std::string MapParser::LOCKEDROOM_NAME = "lockedroom";
    
    const std::string MapParser::ONE_WAY_NAME = "one_way";
    const std::string MapParser::TWO_WAY_NAME = "two_way";
    
    const std::string MapParser::OBJECT_NAME = "object";
    const std::string MapParser::WEAPON_NAME = "weapon";
    const std::string MapParser::ARMOR_NAME = "armor";
    const std::string MapParser::CONTAINER_NAME = "container";
    const std::string MapParser::BACKPACK_NAME = "backpack";
    
    const std::string MapParser::TROLL_NAME = "troll";
    
    const char MapParser::DELIMETER = ';';
    
    
    const int MapParser::MAX_WORLD_SIZE = 200000;
    
    MapParser::MapParser(const std::string& s, 
        std::vector<labgame::Environment*> * _w, Player* _p) :
        world(_w), player(_p)
    {
        this-> filename = s;
    }
    
    void MapParser::evaluate()
    {
        while(!tokens.empty())
        {
            Token specifier = pop();
            
            assert_token(specifier, Token::SPECIFIER);
            
            std::string specifier_data = specifier.get_data_as_string();
            
            std::clog << "Found specifier_data: " << specifier_data << std::endl;
            
            /**
             * HANDLE ROOMS
             **/
            if(is_room(specifier_data))
            {
                Token id_token = pop();
                assert_token(id_token, Token::INT);
                
                int id = id_token.get_data_as_int();
                
                if(id < 1)
                {
                    std::cerr << "Id can't be lower than 1 in input file!" << std::endl;
                    exit(1);
                }
                else if(id > MAX_WORLD_SIZE)
                {
                    std::cerr << "Maps with ids these large are not supported, please lower id " 
                    << id << " on line " << id_token.get_line() << std::endl;
                    exit(1);
                }
                
                if(world->size() < id);
                {
                    world->resize(id);
                }
                Token desc_token = pop();
                
                auto pos = world->begin() + (id-1);
                
                if(specifier_data == ROOM_NAME)
                {
                    world->insert(pos, new Room(id, desc_token.get_data_as_string()));
                    std::clog << "Added new room with id " << id << std::endl;
                }
                else if(specifier_data == FOREST_NAME)
                {
                    Token weather_token = pop();
                    assert_token(weather_token, Token::INT);
                    world->insert(pos, new Forest(id, desc_token.get_data_as_string(),
                        static_cast<Weather::TYPE>(weather_token.get_data_as_int())));
                    std::clog << "Added new forest with id " << id << std::endl;
                }
                else if(specifier_data == LOCKEDROOM_NAME)
                {
                    Token arr_start = pop();
                    assert_token(arr_start, Token::ARRAY_START);
                    
                    std::vector<std::pair<std::string, std::string>> l;
                    
                    while(peek().get_type() == Token::ARRAY_START)
                    {
                        Token s_token = pop();
                        assert_token(s_token, Token::ARRAY_START);
                        Token dir_token = pop();
                        assert_token(dir_token, Token::STRING);
                        Token item_token = pop();
                        assert_token(item_token, Token::STRING);
                        Token e_token = pop();
                        assert_token(e_token, Token::ARRAY_END);
                        
                        l.push_back({dir_token.get_data_as_string(), 
                            item_token.get_data_as_string()});
                    }
                    
                    Token arr_end = pop();
                    assert_token(arr_end, Token::ARRAY_END);
                    
                    world->insert(pos, 
                        new LockedRoom(id, desc_token.get_data_as_string(), l));
                }
                
            }
            
            /**
             * HANDLE LINKS
             **/
            else if(is_link(specifier_data))
            {
                
                Token id_token = pop();
                assert_token(id_token, Token::INT);
                int id = id_token.get_data_as_int();
                
                auto pos = (world->begin() + (id - 1));
                
                Token arr_start = pop();
                assert_token(arr_start, Token::ARRAY_START);
                
                if(specifier_data == TWO_WAY_NAME)
                {
                    while(peek().get_type() == Token::ARRAY_START)
                    {
                        Token s_token = pop();
                        assert_token(s_token, Token::ARRAY_START);
                        Token dir_token = pop();
                        assert_token(dir_token, Token::STRING);
                        Token target_dir_token = pop();
                        assert_token(target_dir_token, Token::STRING);
                        Token target_id_token = pop();
                        assert_token(target_id_token, Token::INT);
                        Token e_token = pop();
                        assert_token(e_token, Token::ARRAY_END);
                        
                        (*world)[id-1]->add_neighbour(dir_token.get_data_as_string(), 
                            target_dir_token.get_data_as_string(), 
                            (*world)[target_id_token.get_data_as_int()-1], true);
                    }
                }
                else if(specifier_data == ONE_WAY_NAME)
                {
                    while(peek().get_type() == Token::ARRAY_START)
                    {
                        Token s_token = pop();
                        assert_token(s_token, Token::ARRAY_START);
                        Token dir_token = pop();
                        assert_token(dir_token, Token::STRING);
                        Token target_id_token = pop();
                        assert_token(target_id_token, Token::INT);
                        Token e_token = pop();
                        assert_token(e_token, Token::ARRAY_END);
                        (*world)[id-1]->add_neighbour(dir_token.get_data_as_string(), 
                            "", (*world)[target_id_token.get_data_as_int()-1], false);
                    }
                }
                Token arr_end = pop();
                assert_token(arr_end, Token::ARRAY_END);
            }
            
            /**
             * HANDLE OBJECTS
             **/
            else if(is_object(specifier_data))
            {
                Token id_token = pop();
                assert_token(id_token, Token::INT);
                
                int id = id_token.get_data_as_int();
                
                Token name_token = pop();
                assert_token(name_token, Token::STRING);
                
                Object * o;
                
                if(specifier_data == OBJECT_NAME)
                {
                    o = new Object(name_token.get_data_as_string());
                }
                else if(specifier_data == WEAPON_NAME)
                {
                    Token damage_token = pop();
                    assert_token(damage_token, Token::INT);
                    o = new Weapon(name_token.get_data_as_string(), damage_token.get_data_as_int());
                }
                else if(specifier_data == ARMOR_NAME)
                {
                    Token armor_token = pop();
                    assert_token(armor_token, Token::INT);
                    Token type_token = pop();
                    assert_token(type_token, Token::INT);
                    
                    Armor::ARMOR_TYPE type = static_cast<Armor::ARMOR_TYPE>(type_token.get_data_as_int());
                    
                    o = new Armor(name_token.get_data_as_string(), armor_token.get_data_as_int(), type);
                }
                else if(specifier_data == CONTAINER_NAME)
                {
                    Token size_token = pop();
                    assert_token(size_token, Token::INT);
                    
                    o = new Container(name_token.get_data_as_string(), size_token.get_data_as_int());
                }
                else if(specifier_data == BACKPACK_NAME)
                {
                    Token size_token = pop();
                    assert_token(size_token, Token::INT);
                    Token strength_token = pop();
                    assert_token(strength_token, Token::INT);
                    Token dexterity_token = pop();
                    assert_token(dexterity_token, Token::INT);
                    Token constitution_token = pop();
                    assert_token(constitution_token, Token::INT);
                    Token intelligence_token = pop();
                    assert_token(intelligence_token, Token::INT);
                    Token wisdom_token = pop();
                    assert_token(wisdom_token, Token::INT);
                    Token charisma_token = pop();
                    assert_token(charisma_token, Token::INT);
                    
                    int strength = strength_token.get_data_as_int();
                    int dexterity = dexterity_token.get_data_as_int();
                    int constitution = constitution_token.get_data_as_int();
                    int intelligence = intelligence_token.get_data_as_int();
                    int wisdom = wisdom_token.get_data_as_int();
                    int charisma = charisma_token.get_data_as_int();
                    
                    o = new Backpack(name_token.get_data_as_string(), size_token.get_data_as_int(), strength, dexterity, constitution, intelligence, wisdom, charisma);
                }
                
                (*world)[id-1]->add_item(o);
            }
            
            /**
             * HANDLE NPCS
             **/
            
            else if(is_npc(specifier_data))
            {
                Token id_token = pop();
                assert_token(id_token, Token::INT);
                Token name_token = pop();
                assert_token(name_token, Token::STRING);
                
                int id = id_token.get_data_as_int() - 1;
                
                if(specifier_data == TROLL_NAME)
                {
                    //Not a memory leak: all npcs are added to a map when created
                    Troll * t = new Troll(name_token.get_data_as_string());
                    t->move_to((*world)[id]);
                }
            }
            
            else if(specifier_data == "player_start")
            {
                Token id = pop();
                assert_token(id, Token::INT);
                this->player_start = id.get_data_as_int();
            }
            
            else
            {
                std::cerr << "Unknown specifier in input file on line " << specifier.get_line() << std::endl;
                exit(1);
            }
            
            Token nl = pop();
            
            assert_token(nl, Token::NEWLINE);
        }
    }
    
    int MapParser::get_player_start() const
    {
        return player_start;
    }
    
    Token MapParser::pop()
    {
        Token t = tokens.front();
        tokens.pop();
        return t;
    }
    
    Token MapParser::peek() const
    {
        Token t = tokens.front();
        return t;
    }
    
    void MapParser::assert_token(Token& t, Token::TOKENTYPE type)
    {
        if(t.get_type() != type)
        {
            std::cerr << "Error in input file on line " << t.get_line() << std::endl;
            std::cerr << "Token was of type: " << token_enum_convert(static_cast<Token::TOKENTYPE>(t.get_type()))<< std::endl;
            std::cerr << "Should have been of type " << token_enum_convert(type) << std::endl;
            exit(1);
        }
    }
    
    std::string MapParser::token_enum_convert(Token::TOKENTYPE t) const
    {
        switch(t)
        {
            case Token::SPECIFIER:
                return "specifier";
                break;
            case Token::NEWLINE:
                return "newline";
                break;
            case Token::INT:
                return "int";
                break;
            case Token::STRING:
                return "string";
                break;
            case Token::ARRAY_START:
                return "array_start";
                break;
            case Token::ARRAY_END:
                return "array_end";
                break;
            default:
                throw std::out_of_range("ENUM NOT FOUND IN TOKEN CONVERT!");
        }
    }
    
    void MapParser::tokenize()
    {
        std::ifstream f;
        f.open(filename);
        
        
        std::string line;
        while(std::getline(f, line))
        {
            currentLineCounter++;
            if(line == "")
            {
                
                continue;
            }
            parse(line);
            lineCounter = 0;
        }
        
    }
    
    bool MapParser::is_room(std::string& name) const
    {
        if(name == FOREST_NAME || name == ROOM_NAME || name == LOCKEDROOM_NAME )
        {
            return true;
        }
        return false;
    }
    
    bool MapParser::is_link(std::string& name) const
    {
        if(name == ONE_WAY_NAME || name == TWO_WAY_NAME)
        {
            return true;
        }
        return false;
    }
    
    bool MapParser::is_object(std::string& name) const
    {
        if(name == OBJECT_NAME || name == WEAPON_NAME || name == ARMOR_NAME || name == BACKPACK_NAME || name == CONTAINER_NAME)
        {
            return true;
        }
        return false;
    }
    
    bool MapParser::is_npc(std::string& name) const
    {
        if(name == TROLL_NAME)
        {
            return true;
        }
        return false;
    }
    
    void MapParser::parse(std::string& line)
    {
        std::string n = stringtok(line, ':');
        tokens.push(Token(Token::SPECIFIER, n, currentLineCounter));
        parse_arguments(line);
        tokens.push(Token(Token::NEWLINE, "\n", currentLineCounter));
    }
    
    void MapParser::parse_arguments(std::string& line)
    {
        std::string t;
        while( !(t = stringtok(line, DELIMETER)).empty())
        {
            if(is_number(t))
            {
                tokens.push(Token(Token::INT, t, currentLineCounter));
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
                tokens.push(Token(Token::ARRAY_START, "[", currentLineCounter));

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
                if(lineCounter != line.length() && line.at(lineCounter) == DELIMETER)
                {
                    ++lineCounter;
                }
                
                tokens.push(Token(Token::ARRAY_END, "]", currentLineCounter));
            }
            else
            {
                tokens.push(Token(Token::STRING, t, currentLineCounter));
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
}