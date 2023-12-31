#include "includes/Location.hpp"
#include "includes/Server.hpp"
#include "includes/Error.hpp"
#include "includes/parser/Lexer.hpp"

int main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cerr << USAGE << std::endl ;
		return (2) ;
	}

	try
	{
		Lexer::checkSyntax(argv[1]) ;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl ;
	}

	return (0) ;
}
