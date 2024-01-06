#include "../includes/Server.hpp"

Server::Server( void ) : _serverName(""), _port(), _root(""), _host(""), _clientMaxBodySize(), _errorPage("")
{
    // std::cerr << __PRETTY_FUNCTION__ << std::endl ;
    // this->_locations.insert(std::make_pair(
    //     "/",
    //     Location() 
    // )) ;
}

Server::Server( const Server& rhs )
{
    // std::cerr << __PRETTY_FUNCTION__ << std::endl ;
    this->_serverName = rhs._serverName ;
    this->_port = rhs._port ;
    this->_host = rhs._host ;
    this->_root = rhs._root ;
    this->_index = rhs._index ;
    this->_clientMaxBodySize = rhs._clientMaxBodySize ;
    this->_errorPage = rhs._errorPage ;

    std::map<std::string, Location>::const_iterator it = rhs._locations.begin() ;
    while (rhs._locations.size() &&  it != rhs._locations.begin())
    {
        this->_locations.insert(*it++) ;
    }
}

Server& Server::operator=( const Server& rhs )
{
    std::cerr << __PRETTY_FUNCTION__ << std::endl ;
    this->_serverName = rhs._serverName ;
    this->_port = rhs._port ;
    this->_host = rhs._host ;
    this->_root = rhs._root ;
    this->_index = rhs._index ;
    this->_clientMaxBodySize = rhs._clientMaxBodySize ;
    this->_errorPage = rhs._errorPage ;

    std::map<std::string, Location>::const_iterator it = rhs._locations.begin() ;
    this->_locations.clear() ;
    while (it != rhs._locations.begin())
        this->_locations.insert(*it) ;
    return (*this) ;
}

Server::~Server( void )
{
    // std::cerr << __PRETTY_FUNCTION__ << std::endl ;
}

const std::string&						Server::getServerName ( void ) const
{
    return (_serverName) ;
}

const std::string&						Server::getIndex ( void ) const
{
    return (_index) ;
}

const size_t&							Server::getPort ( void ) const
{
    return (_port) ;
}

const std::string&						Server::getRoot ( void ) const
{
    return (_root) ;
}

const std::string&						Server::getHost ( void ) const
{
    return (_host) ;
}

const size_t&							Server::getClientMaxBodySize ( void ) const
{
    return (_clientMaxBodySize) ;
}

const std::string&						Server::getErrorPage ( void ) const
{
    return (_errorPage) ;
}

const std::map<std::string, Location>&	Server::getLocations ( void ) const
{
    return (_locations) ;
}

void 							Server::setServerName( const std::string& _serverName )
{
    this->_serverName = _serverName ;
}

void 							Server::setIndex( const std::string& _index )
{
    this->_index = _index ;
}

void 							Server::setPort( const size_t& _port )
{
    this->_port = _port ;
}

void 							Server::setRoot( const std::string& _root )
{
    this->_root = _root ;
}

void 							Server::setHost( const std::string& _host )
{
    this->_host = _host ;
}

void 							Server::setClientMaxBodySize( const size_t& _clientMaxBodySize )
{
    this->_clientMaxBodySize = _clientMaxBodySize ;
}

void 							Server::setErrorPage( const std::string& _errorPage )
{
    this->_errorPage = _errorPage ;
}

void 							Server::setLocations( const Locations_t& _locations )
{
    this->_locations = _locations ;
}

void 							Server::appendLocation( const std::string& path, const Location& _location )
{
    this->_locations[path] = _location ;
}



std::ostream& operator<<( std::ostream& os, const Server& server )
{
    os << "Server Name: " << server.getServerName() << std::endl ;
    os << "Index: " << server.getIndex() << std::endl ;
    os << "Port: " << server.getPort() << std::endl ;
    os << "Root: " << server.getRoot() << std::endl ;
    os << "Host: " << server.getHost() << std::endl ;
    os << "Client Max Body Size: " << server.getClientMaxBodySize() << std::endl ;
    os << "Error Page: " << server.getErrorPage() << std::endl ;

    os << "Locations: " << std::endl ;
    Server::Locations_t locations = server.getLocations() ;
    Server::Locations_t::const_iterator it = locations.begin() ;
    std::cout << "----------------------------" << std::endl ;
    while (it != locations.end())
    {
        std::cout << "--------------" << std::endl ;
        os << it->first << ": " << std::endl << it->second ;
        it++ ;
        std::cout << "--------------" << std::endl ;
    }
    std::cout << "----------------------------" << std::endl ;
    return (os) ;
}