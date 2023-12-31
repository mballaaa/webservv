#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
private:
	bool						_autoIndex ;
	std::string					_index ;
	Methods_t					_allowedMethods ;
	std::string					_return ;
	std::string					_root ;
	std::string					_cgiPath ;
	std::string					_cgiExtention ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::string&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const std::string&			getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const std::string&			getCgiPath( void ) const ;
	const std::string&			getCgiExtention( void ) const ;

	// Setters
	void 						setAutoIndex( const bool& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgiPath( const std::string& _cgiPath ) ;
	void 						setCgiExtention( const std::string& _cgiExtention ) ;
} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
