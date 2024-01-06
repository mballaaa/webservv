#include "includes/Location.hpp"
#include "includes/Server.hpp"
#include "includes/Error.hpp"
#include "includes/parser/Lexer.hpp"
#include "includes/parser/Parser.hpp"

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
	std::vector<Server> servers ;
	try
	{
		tokens = Lexer::checkSyntax(argv[1]) ;
		Parser::servers_t t = Parser::createServers(tokens) ;
		std::for_each(t.begin(), t.end(), print) ;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl ;
	}

	return (0) ;
}
