#include "includes/Location.hpp"
#include "includes/Server.hpp"
#include "includes/Error.hpp"
#include "includes/parser/Lexer.hpp"

#include <cstdlib>

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
		while (!tokens.empty())
		{
			Server s ;
			if (tokens.front() == "server")
			{
				tokens.pop_front() ;
				tokens.pop_front() ;
				while (tokens.front() != "}")
				{
					if (tokens.front() == "listen")
					{
						tokens.pop_front() ;
						s.setPort(atol(tokens.front().c_str())) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "server_name")
					{
						tokens.pop_front() ;
						s.setServerName(tokens.front()) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "host")
					{
						tokens.pop_front() ;
						s.setHost(tokens.front()) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "root")
					{
						tokens.pop_front() ;
						s.setRoot(tokens.front()) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "client_max_body_size")
					{
						tokens.pop_front() ;
						s.setClientMaxBodySize(atol(tokens.front().c_str())) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "index")
					{
						tokens.pop_front() ;
						s.setIndex(tokens.front()) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "error_page")
					{
						tokens.pop_front() ;
						tokens.pop_front() ;
						s.setErrorPage(tokens.front()) ;
						tokens.pop_front() ;
						tokens.pop_front() ;
					}
					if (tokens.front() == "location")
					{
						tokens.pop_front() ;
						std::string path = tokens.front() ;
						tokens.pop_front() ;
						tokens.pop_front() ;
						Location l ;
							if (tokens.front() == "allow_methods")
							{
								tokens.pop_front() ;
								Location::Methods_t m ;
								while (tokens.front() != ";")
								{
									if (tokens.front() == "GET")
										m.push_back(Location::GET) ;
									else if (tokens.front() == "DELETE")
										m.push_back(Location::DELETE) ;
									else if (tokens.front() == "POST")
										m.push_back(Location::POST) ;
									else if (tokens.front() == "PUT")
										m.push_back(Location::PUT) ;
									else if (tokens.front() == "HEAD")
										m.push_back(Location::HEAD) ;
									tokens.pop_front() ;
								}
								l.setAllowedMethods(m) ;
								tokens.pop_front() ;
							}
							if (tokens.front() == "autoindex")
							{
								tokens.pop_front() ;
								l.setAutoIndex(tokens.front() == "on" ? true : false) ;
								tokens.pop_front() ;
								tokens.pop_front() ;
							}
							if (tokens.front() == "autoindex")
							{
								tokens.pop_front() ;
								l.setAutoIndex(tokens.front() == "on" ? true : false) ;
								tokens.pop_front() ;
							}
							if (tokens.front() == "root")
							{
								tokens.pop_front() ;
								l.setRoot(tokens.front()) ;
								tokens.pop_front() ;
								tokens.pop_front() ;
							}
							std::cout << tokens.front() << std::endl ;
							exit(0) ;
							if (tokens.front() == "cgi_path")
							{
								tokens.pop_front() ;
								l.setCgiPath(tokens.front()) ;
								while (tokens.front() != ";")
									tokens.pop_front() ;
								tokens.pop_front() ;
							}
							if (tokens.front() == "cgi_ext")
							{
								tokens.pop_front() ;
								l.setCgiExtention(tokens.front()) ;
								while (tokens.front() != ";")
									tokens.pop_front() ;
								tokens.pop_front() ;
							}
						s.appendLocation(path, l) ;
						tokens.pop_front() ;
						while (tokens.front() != "}")
							tokens.pop_front() ;
						tokens.pop_front() ;
					}
				}
				tokens.pop_front() ;
			}
			std::cout << s << std::endl ;
		}
		
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl ;
	}

	return (0) ;
}
