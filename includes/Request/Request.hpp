#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../Server.hpp"

class Request
{
public:
private:
    const Server&   owner ;
	const int       socketfd ;
	Request& operator=( const Request& rhs ) ;
	Request( void ) ;

public:
    std::string request ;
	Request( const int& socketfd, const Server& owner ) ;
	Request( const Request& rhs ) ;
	~Request( void ) ;

	// Getters
	const int&          			getSocketFD( void ) const ;
	const Server& 					getServer( void ) const ;

} ;

std::ostream& operator<<( std::ostream& os, const Request& server ) ;

#endif
