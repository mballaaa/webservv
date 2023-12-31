#include "includes/Location.hpp"
#include "includes/Server.hpp"
#include <fstream>
#include <sstream>
#include <list>
#include <iomanip>

typedef enum { SERVER, OCB, CCB, PARAM, LOCATION, SEMICOLON, ERROR } sym_t ;
std::list<std::string> g_tokens ;
std::list<std::string>::iterator g_it = g_tokens.begin() ;
sym_t sym = ERROR;

std::list<std::string> lexer( const std::string& configPath )
{
	std::ifstream configFile(configPath.c_str()) ;
	if (!configFile)
		throw std::runtime_error("Couldn't open: " + configPath) ;
	if (configFile.peek() == std::ifstream::traits_type::eof())
		throw std::runtime_error("Confing file is empty") ;

	std::stringstream ss ;
	ss << configFile.rdbuf() ;
	configFile.close() ;

	std::string token ;
	std::list<std::string> tokens ;
	while (ss >> token)
	{
		size_t scPos = token.find(';') ;
		if (scPos != std::string::npos)
		{
			tokens.push_back(token.substr(0, scPos)) ;
			tokens.push_back(token.substr(scPos)) ;
		}
		else
			tokens.push_back(token) ;
	}

	// std::list<std::string>::iterator it = tokens.begin() ;
	// while (it != tokens.end())
	// 	std::cout << *it++ << std::endl ;
	return (tokens) ;
}

std::string getSymbolName( const sym_t& s )
{
	if ( s == SERVER)
		return std::string("SERVER") ;
	else if ( s == OCB)
		return std::string("OCB") ;
	else if ( s == CCB)
		return std::string("CCB") ;
	else if ( s == LOCATION)
		return std::string("LOCATION") ;
	else if ( s == SEMICOLON)
		return std::string("SEMICOLON") ;
	return std::string("PARAM") ;
}

void nextSym( void )
{
	if (*g_it == "server")
		sym = SERVER ;
	else if (*g_it == "{")
		sym = OCB ;
	else if (*g_it == "}")
		sym = CCB ;
	else if (*g_it == "location")
		sym = LOCATION ;
	else if (*g_it == ";")
		sym = SEMICOLON ;
	else
		sym = PARAM ;
	// std::cout << std::setw(10) << std::left << getSymbolName(sym) << " ";
	// std::cout << *g_it << std::endl ;
	g_it++ ;
}

bool accept(sym_t s) {
    if (sym == s) {
        ::nextSym();
        return (true);
    }
    return (false);
}

bool	expect( sym_t s )
{
	if (accept(s))
		return (true) ;
	throw std::runtime_error("expect: unexpected symbol " + getSymbolName(sym)) ;
	return (false) ;
}

void param( void )
{
	if (accept(PARAM))
	while (accept(PARAM)) ;
	::expect(SEMICOLON) ;
}

void location( void )
{
	::expect(LOCATION) ;
	::expect(PARAM) ;
	::expect(OCB) ;
	while (sym == PARAM)
		param() ;
	::expect(CCB) ;
}

int main( int argc, char **argv )
{
	if (argc != 2)
		return (2) ;

	g_tokens = ::lexer(argv[1]) ;
	g_it = g_tokens.begin() ;
	

	nextSym() ;
	::expect(SERVER) ;
	::expect(OCB) ;
	while (sym == PARAM || sym == LOCATION)
	{
		if (sym == PARAM)
			param() ;
		else
			location() ;
	}
	::expect(CCB) ;

	return (0) ;
}
