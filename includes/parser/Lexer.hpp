#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <iomanip>

class Lexer
{
public:
    typedef enum { SERVER, OCB, CCB, PARAM, LOCATION, ERR_PAGE, ALLOW_METHODS, CGI_PATH,
    CGI_EXT, SEMICOLON, ERROR } sym_t ;
    typedef std::string token_t ;
    typedef std::list<std::string> tokens_t ;
    typedef tokens_t::const_iterator iterator_t ;

    static tokens_t checkSyntax( const std::string& configPath ) ;

private:
    static tokens_t tokens ;
    static iterator_t it ;
    static sym_t    sym ;

    static tokens_t lexer( const std::string& configPath ) ;
    static std::string getSymbolName( const sym_t& s ) ;
    static void nextSym( void ) ;
    static bool accept(sym_t s) ;
    static bool	expect( sym_t s ) ;

    static void param( void ) ;
    static void location( void ) ;
    static void errPage( void ) ;
    static void allowMethods( void ) ;
    static void cgiPath( void ) ;
    static void cgiExt( void ) ;

    Lexer( void );
    Lexer( const Lexer& rhs );
    Lexer& operator=( const Lexer& rhs );
    ~Lexer( void );    
};

#endif