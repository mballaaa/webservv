#ifndef MULTIPLEX_HPP
#define MULTIPLEX_HPP

#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <string>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>

#include "SocketManager.hpp"
#include "Server.hpp"

class Multiplex
{
public:
	typedef std::vector<Server> servers_t ;
private:
    static servers_t servers ;
	Multiplex( void ) ;
	Multiplex( const Multiplex& rhs ) ;
	Multiplex& operator=( const Multiplex& rhs ) ;
	~Multiplex( void ) ;
public:
    static void setServers( const servers_t& servers ) ;
    static void start( void ) ;
    static void setup( const Server& server ) ;

	// Getters

	// Setters
} ;

std::ostream& operator<<( std::ostream& os, const Multiplex& server ) ;

#endif
