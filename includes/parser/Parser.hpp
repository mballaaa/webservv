#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <iomanip>
#include <cstdlib>

#include "../../includes/parser/Lexer.hpp"
#include "../../includes/Server.hpp"

class Parser
{
public:
    typedef std::vector<Server> servers_t ;

    static servers_t createServers( const Lexer::tokens_t& tokens ) ;

private:
    static servers_t servers ;
    static Lexer::iterator_t token ;
    static Lexer::iterator_t tokenEnd ;

    static servers_t parse( Lexer::iterator_t start ) ;
    static void nextSym( void ) ;
    static bool accept( Lexer::token_t sym, bool increment = true ) ;
    static void server( Lexer::iterator_t curr ) ;
    static void location( Lexer::iterator_t curr ) ;
    // static bool	expect( Lexer::token_t token ) ;

    Parser( void );
    Parser( const Parser& rhs );
    Parser& operator=( const Parser& rhs );
    ~Parser( void );  
};

#endif