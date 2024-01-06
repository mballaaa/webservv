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
		// ignore comments from config file
		if (token.find('#') != std::string::npos)
		{
			getline(ss, token) ;
			continue ;
		}
		size_t scPos = token.find(';') ; // find semicolon
		// split by semicolon so the semicolon is a token by it self
		if (scPos != std::string::npos && scPos)
		{
			std::string param(token.substr(0, scPos)) ;
			std::string semi(token.substr(scPos)) ;
			tokens.push_back(param) ;
			tokens.push_back(semi) ;
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
	else if (s == ERR_PAGE)
		return std::string("ERR_PAGE") ;
	else if (s == ALLOW_METHODS)
		return std::string("ALLOW_METHODS") ;
	else if (s == CGI_PATH)
		return std::string("CGI_PATH") ;
	else if (s == CGI_EXT)
		return std::string("CGI_EXT") ;
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
	else if (*it == "error_page")
		sym = ERR_PAGE ;
	else if (*it == "allow_methods")
		sym = ALLOW_METHODS ;
	else if (*it == "cgi_path")
		sym = CGI_PATH ;
	else if (*it == "cgi_ext")
		sym = CGI_EXT ;
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
	throw std::runtime_error("expect: unexpected symbol " + *it + " " + getSymbolName(s)) ;
	return (false) ;
}

void Lexer::param( void )
{
	expect(PARAM) ;
	expect(PARAM) ;
	expect(SEMICOLON) ;
}

void Lexer::location( void )
{
	expect(LOCATION) ;
	expect(PARAM) ;
	expect(OCB) ;
	while (sym == PARAM || sym == ERR_PAGE || sym == ALLOW_METHODS || sym == CGI_PATH || sym == CGI_EXT)
	{
		if (sym == PARAM)
			param() ;
		else if (sym == ERR_PAGE)
			errPage() ;
		else if (sym == ALLOW_METHODS)
			allowMethods() ;
		else if (sym == CGI_PATH)
			cgiPath() ;
		else if (sym == CGI_EXT)
			cgiExt() ;
	}
	expect(CCB) ;
}

void Lexer::errPage( void )
{
	expect(ERR_PAGE) ;
	expect(PARAM) ;
	expect(PARAM) ;
	expect(SEMICOLON) ;
}

void Lexer::allowMethods( void )
{
	expect(ALLOW_METHODS) ;
	while (accept(PARAM)) ;
	expect(SEMICOLON) ;
}

void Lexer::cgiPath( void )
{
	expect(CGI_PATH) ;
	while (accept(PARAM)) ;
	expect(SEMICOLON) ;
}

void Lexer::cgiExt( void )
{
	expect(CGI_EXT) ;
	while (accept(PARAM)) ;
	expect(SEMICOLON) ;
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