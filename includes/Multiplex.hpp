#ifndef MULTIPLEX_HPP
#define MULTIPLEX_HPP

#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Server.hpp"
#include <netdb.h>
#include <fcntl.h>

#include "SocketManager.hpp"

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
