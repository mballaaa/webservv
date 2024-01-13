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
		size_t scPos = 0 ;
		size_t scPrev = 0 ;
		std::string delimiters("{}; ") ;
		// split by semicolon so the semicolon is a token by it self
		while ((scPos = token.find_first_of(delimiters, scPrev)) != std::string::npos)
		{
			if (scPos > scPrev)
				tokens.push_back(token.substr(scPrev, scPos - scPrev)) ;
			tokens.push_back(token.substr(scPos, 1)) ;
			scPrev = scPos + 1 ;
		}
		if (scPrev < token.length())
			tokens.push_back(token.substr(scPrev)) ;
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
	else if (s == CGI)
		return std::string("CGI") ;
	else if (s == MULTIPLE_P)
		return std::string("MULTI_P") ;
	return std::string("SINGLE_P") ;
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
	else if (*it == "cgi")
		sym = CGI ;
	else if (*it == "server_name")
		sym = MULTIPLE_P ;
	else
		sym = SINGLE_P ;
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
	throw std::runtime_error("expect: " + getSymbolName(s) + " unexpected symbol " + *it) ;
	return (false) ;
}

void Lexer::signleParam( void )
{
	expect(SINGLE_P) ;
	expect(SINGLE_P) ;
	expect(SEMICOLON) ;
}

void Lexer::multipleParam( void )
{
	expect(MULTIPLE_P) ;
	expect(SINGLE_P) ;
	while (accept(SINGLE_P)) ;
	expect(SEMICOLON) ;
}

void Lexer::location( void )
{
	expect(LOCATION) ;
	std::string path(*it) ;
	expect(SINGLE_P) ;
	expect(OCB) ;
	while (sym == SINGLE_P || sym == ERR_PAGE || sym == ALLOW_METHODS || sym == CGI || sym == MULTIPLE_P )
	{
		if (sym == SINGLE_P)
			signleParam() ;
		else if (sym == ERR_PAGE)
			errPage() ;
		else if (sym == ALLOW_METHODS)
			allowMethods() ;
		else if (sym == CGI)
			cgi() ;
	}
	expect(CCB) ;
}

void Lexer::errPage( void )
{
	expect(ERR_PAGE) ;
	expect(SINGLE_P) ;
	expect(SINGLE_P) ;
	expect(SEMICOLON) ;
}

void Lexer::allowMethods( void )
{
	expect(ALLOW_METHODS) ;
	while (accept(SINGLE_P)) ;
	expect(SEMICOLON) ;
}

void Lexer::cgi( void )
{
	expect(CGI) ;
	expect(SINGLE_P) ;
	expect(SEMICOLON) ;
}


Lexer::tokens_t Lexer::checkSyntax( const std::string& configPath )
{
    tokens = lexer(configPath) ;
	it = tokens.begin() ;
    nextSym() ;
	while (accept(SERVER))
	{
		expect(OCB) ;
		while (sym != CCB)
		{
			if (sym == LOCATION)
				location() ;
			else if (sym == ERR_PAGE)
				errPage() ;
			else if (sym == MULTIPLE_P)
				multipleParam() ;
			else
				signleParam() ;
		}
		expect(CCB) ;
	}
	return (tokens) ;
}