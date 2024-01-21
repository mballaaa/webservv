#include "../../includes/Request/Request.hpp"

const int&          			Request::getSocketFD( void ) const
{
    return (socketfd) ;
}

const Server& 					Request::getServer( void ) const
{
    return (owner) ;
}

Request::Request( const int& socketfd, const Server& owner ) : owner(owner), socketfd(socketfd), request()
{
}

Request::Request( const Request& rhs ) : owner(rhs.owner), socketfd(rhs.socketfd), request(rhs.request)
{
}

Request::~Request( void )
{   
}

Request& Request::operator=( const Request& rhs )
{
    (void) rhs ;
    return (*this) ;
}