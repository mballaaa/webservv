#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <iomanip>
#include <map>
#include "Location.hpp"

class Server
{
public:
	typedef std::map<std::string, Location> Locations_t ;
	typedef std::vector<std::string> serverNames_t ;
	typedef std::map<int, std::string> errorPages_t ;
private:
	serverNames_t				_serverNames ;
	std::vector<std::string>	_index ;
	std::string					_port ;
	std::string					_root ;
	std::string					_host ;
	size_t						_clientMaxBodySize ;
	errorPages_t				_errorPages ;
	Locations_t					_locations ;

	int socketfd ;

public:
	Server( void ) ;
	Server( const Server& rhs ) ;
	Server& operator=( const Server& rhs ) ;
	~Server( void ) ;

	// Getters
	const serverNames_t&			getServerNames ( void ) const ;
	const std::vector<std::string>&				getIndex ( void ) const ;
	const std::string&				getPort ( void ) const ;
	const std::string&				getRoot ( void ) const ;
	const std::string&				getHost ( void ) const ;
	const size_t&					getClientMaxBodySize ( void ) const ;
	const errorPages_t&				getErrorPages ( void ) const ;
	const Locations_t&				getLocations ( void ) const ;

	// Setters
	void 							setServerNames( const serverNames_t& serverNames ) ;
	void 							setIndex( const std::string& _Index ) ;
	void 							setPort( const std::string& _port ) ;
	void 							setRoot( const std::string& _root ) ;
	void 							setHost( const std::string& _host ) ;
	void 							setClientMaxBodySize( const size_t& _clientMaxBodySize ) ;
	void 							setErrorPages( const errorPages_t& _errorPage ) ;
	void 							setLocations( const Locations_t& _locations ) ;
	void 							setSocketFD( const int& fd ) ;

	void 							appendLocation( const std::string& path, const Location& _location ) ;
	void 							appendErrorPage( const int& statusCode, const std::string& errorPagePath ) ;
	void 							appendServerName( const std::string& serverName ) ;
} ;

std::ostream& operator<<( std::ostream& os, const Server& server ) ;

#endif
