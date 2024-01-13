#include "includes/Location.hpp"
#include "includes/Server.hpp"
#include "includes/Error.hpp"
#include "includes/parser/Parser.hpp"
#include "includes/parser/Lexer.hpp"

#include <cstdlib>
#include <algorithm>

static void print(Server s)
{
	std::cout << s << std::endl ;
}

int main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cerr << USAGE << std::endl ;
		return (2) ;
	}

	Lexer::tokens_t tokens ;
	try
	{
		tokens = Lexer::checkSyntax(argv[1]) ;
		Parser::servers_t servers = Parser::parse(tokens) ;
		std::for_each(servers.begin(), servers.end(), print) ;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl ;
	}

	return (0) ;
}
