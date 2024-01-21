#ifndef HEADER_HPP
#define HEADER_HPP


class Header
{
private:
    // accept

public:
	Header( const Header& rhs ) ;
	~Header( void ) ;

	// Getters
	const int&          			getSocketFD( void ) const ;
	const Server& 					getServer( void ) const ;

} ;

std::ostream& operator<<( std::ostream& os, const Header& server ) ;

#endif
