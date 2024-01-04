#include "../../includes/parser/Lexer.hpp"

Lexer::tokens_t Lexer::tokens ;
Lexer::iterator_t Lexer::it ;
Lexer::sym_t Lexer::sym = Lexer::ERROR ;

Lexer::tokens_t Lexer::lexer( const std::string& configPath )
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

std::string Lexer::getSymbolName( const sym_t& s )
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

void Lexer::nextSym( void )
{
	if (*it == "server")
		sym = SERVER ;
	else if (*it == "{")
		sym = OCB ;
	else if (*it == "}")
		sym = CCB ;
	else if (*it == "location")
		sym = LOCATION ;
	else if (*it == ";")
		sym = SEMICOLON ;
	else
		sym = PARAM ;
	// std::cout << std::setw(10) << std::left << getSymbolName(sym) << " ";
	// std::cout << *it << std::endl ;
	it++ ;
}

bool Lexer::accept(sym_t s)
{
    if (sym == s) {
        nextSym();
        return (true) ;
    }
    return (false) ;
}

bool	Lexer::expect( sym_t s )
{
	if (accept(s))
		return (true) ;
	throw std::runtime_error("expect: unexpected symbol " + *--it) ;
	return (false) ;
}

void Lexer::param( void )
{
	if (accept(PARAM))
	while (accept(PARAM)) ;
	expect(SEMICOLON) ;
}

void Lexer::location( void )
{
	expect(LOCATION) ;
	expect(PARAM) ;
	expect(OCB) ;
	while (sym == PARAM)
		param() ;
	expect(CCB) ;
}

Lexer::tokens_t Lexer::checkSyntax( const std::string& configPath )
{
    tokens = lexer(configPath) ;
	it = tokens.begin() ;
    nextSym() ;
	expect(SERVER) ;
	expect(OCB) ;
	while (sym == PARAM || sym == LOCATION)
	{
		if (sym == PARAM)
			param() ;
		else
			location() ;
	}
	expect(CCB) ;
	return (tokens) ;
}