#ifndef SOCKET_MANAGER_HPP
#define SOCKET_MANAGER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

class SocketManager
{
private:
    static int epollFD ;

    SocketManager( void ) ;
    ~SocketManager( void ) ;
    SocketManager( const SocketManager& rhs ) ;
    const SocketManager& operator=( const SocketManager& rhs ) ;
    
public:
    static int createSocket( const char *host, const char *port, int ai_family = AF_INET, int ai_socktype = SOCK_STREAM, int ai_flags = 0) ;
    static int makeSocketNonBlocking( int sfd ) ;
    static int startListening( int sfd ) ;
    static int createEpoll( void ) ;
    static int epollAddSocket( int sfd ) ;

};


#endif