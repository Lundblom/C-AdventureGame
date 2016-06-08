#include <string>
#include <vector>
#include <queue>

#include "Token.h"
#include "Player.h"
#include "Environment.h"
#pragma once
namespace labgame
{
    class MapParser
    {
        private:
        
        
        
        static const int MAX_WORLD_SIZE;
        
        //References
        std::vector<labgame::Environment*> * world;
        Player ** player;
        
        
        int lineCounter = 0;
        int player_start = 1;
        
        int currentLineCounter = 0;
        
        std::string filename;
        std::queue<Token> tokens;
        
        std::size_t find_parenthesis_end(const std::string& s);
        std::string stringtok(const std::string&, char);
        bool is_number(const std::string&) const;
        void parse_arguments(std::string&);
        
        std::string token_enum_convert(Token::TOKENTYPE) const;
        
        //Evaluating categories
        bool is_room(std::string&) const;
        bool is_link(std::string&) const;
        bool is_object(std::string&) const;
        bool is_npc(std::string&) const;
        
        void assert_token(Token&, Token::TOKENTYPE);
        
        Token pop();
        Token peek() const;
        
        public:
        
        static const std::string FOREST_NAME;
        static const std::string ROOM_NAME;
        static const std::string LOCKEDROOM_NAME;
        
        static const std::string ONE_WAY_NAME;
        static const std::string TWO_WAY_NAME;
        
        static const std::string OBJECT_NAME;
        static const std::string WEAPON_NAME;
        static const std::string ARMOR_NAME;
        static const std::string CONTAINER_NAME;
        static const std::string BACKPACK_NAME;
        static const std::string HEALTHPOTION_NAME;
        
        static const std::string PLAYER_START;
        
        static const std::string WIZARD_NAME;
        
        static const std::string TROLL_NAME;
        
        static const char DELIMETER;
        static const char SPECIFIER_DELIMETER;
        static const char ARRAY_START;
        static const char ARRAY_END;
        
        MapParser();
        MapParser(const std::string&, std::vector<labgame::Environment*> *, Player**);
        
        void tokenize();
        void parse(std::string&);
        void evaluate();
        
        int get_player_start() const;
    };
}