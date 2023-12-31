#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <sstream>
#include <list>
#include <iomanip>

class Lexer
{
public:
    typedef enum { SERVER, OCB, CCB, PARAM, LOCATION, SEMICOLON, ERROR } sym_t ;
    typedef std::list<std::string> tokens_t ;
    typedef tokens_t::iterator iterator_t ;

    static void checkSyntax( const std::string& configPath ) ;

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

    Lexer( void );
    Lexer( const Lexer& rhs );
    Lexer& operator=( const Lexer& rhs );
    ~Lexer( void );    
};

#endif