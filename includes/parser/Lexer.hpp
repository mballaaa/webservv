#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <iomanip>
#include <cstring>

#include "../Server.hpp"

class Lexer
{
public:
    typedef enum { SINGLE_P, SERVER, OCB, CCB, MULTIPLE_P, LOCATION, ERR_PAGE, RETURN, ALLOW_METHODS, CGI, SEMICOLON, ERROR } sym_t ;
    typedef std::string token_t ;
    typedef std::list<std::string> tokens_t ;
    typedef tokens_t::const_iterator iterator_t ;
    typedef std::map<Lexer::sym_t, std::string> sym_names_t ;
    typedef std::map<std::string, Lexer::sym_t> name_sym_t ;


    static tokens_t checkSyntax( const std::string& configPath ) ;

    static sym_names_t symNames ;
    static name_sym_t nameSyms ;
private:
    static tokens_t tokens ;
    static iterator_t it ;
    static iterator_t prev ;
    static sym_t    sym ;

    static tokens_t lexer( const std::string& configPath ) ;
    static std::string getSymbolName( const sym_t& s ) ;
    static void nextSym( void ) ;
    static bool accept(sym_t s) ;
    static bool	expect( sym_t s ) ;

    static void signleParam( void ) ;
    static void multipleParam( void ) ;
    static void location( void ) ;
    static void errPage( void ) ;
    static void _return( void ) ;
    static void allowMethods( void ) ;
    static void cgi( void ) ;

    Lexer( void );
    Lexer( const Lexer& rhs );
    Lexer& operator=( const Lexer& rhs );
    ~Lexer( void );    
};

#endif