#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <map>
#include "Location.hpp"

class Server
{
public:
	typedef std::map<std::string, Location> Locations_t ;
private:
	std::string						_serverName ;
	std::string						_index ;
	size_t							_port ;
	std::string						_root ;
	std::string						_host ;
	size_t							_clientMaxBodySize ;
	std::string						_errorPage ;
	Locations_t						_locations ;
public:
	Server( void ) ;
	Server( const Server& rhs ) ;
	Server& operator=( const Server& rhs ) ;
	~Server( void ) ;

	// Getters
	const std::string&				getServerName ( void ) const ;
	const std::string&				getIndex ( void ) const ;
	const size_t&					getPort ( void ) const ;
	const std::string&				getRoot ( void ) const ;
	const std::string&				getHost ( void ) const ;
	const size_t&					getClientMaxBodySize ( void ) const ;
	const std::string&				getErrorPage ( void ) const ;
	const Locations_t&				getLocations ( void ) const ;

	// Setters
	void 							setServerName( const std::string& _serverName ) ;
	void 							setIndex( const std::string& _Index ) ;
	void 							setPort( const size_t& _port ) ;
	void 							setRoot( const std::string& _root ) ;
	void 							setHost( const std::string& _host ) ;
	void 							setClientMaxBodySize( const size_t& _clientMaxBodySize ) ;
	void 							setErrorPage( const std::string& _errorPage ) ;
	void 							setLocations( const Locations_t& _locations ) ;
	void 							appendLocation( const std::string& path, const Location& _location ) ;
} ;

std::ostream& operator<<( std::ostream& os, const Server& server ) ;

#endif
