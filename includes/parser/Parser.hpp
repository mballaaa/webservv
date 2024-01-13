#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <iomanip>
#include <cstdlib>

#include "../Server.hpp"
#include "./Lexer.hpp"

class Parser
{
public:
    typedef std::vector<Server> servers_t ;

    static servers_t parse( const Lexer::tokens_t& tokens ) ;
private:
    static servers_t servers ;
    static Lexer::iterator_t curr ;
    static Lexer::iterator_t end ;

    static bool next( void ) ;
    static bool expect( const std::string& sym ) ;
    static bool accept( const std::string& sym ) ;
    static Server createServer( void ) ;
    static Location createLocation( void ) ;

    Parser( void ) ;
    Parser( const Parser& rhs ) ;
    Parser& operator=( const Parser& rhs ) ;
    ~Parser( void ) ;
};


#endif