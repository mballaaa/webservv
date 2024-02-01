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
    typedef void (*setter_func_t)() ;

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

    // Server Context

    static void _listen( Server& s ) ;
    static void _serverName( Server& s ) ;
    static void _host( Server& s ) ;
    static void _clientMaxBodySize( Server& s ) ;
    static void _index( Server& s ) ;
    static void _errorPage( Server& s ) ;
    static void _location( Server& s ) ;
    static void _autoIndex( Server& s ) ;
    static void _root( Server& s ) ;

    // Location Context

    static void _autoIndex( Location& s ) ;
    static void _index( Location& s ) ;
    static void _allowMethods( Location& s ) ;
    static void _return( Location& s ) ;
    static void _root( Location& s ) ;
    static void _cgi( Location& s ) ;



};


#endif