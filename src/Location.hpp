#include "../includes/Location.hpp"

Location::Location( void ) : _autoIndex(false), _index(""), _allowedMethods(), _return(), _root(""), _cgiPath(), _cgiExtention() 
{
}

Location::Location( const Location& rhs )
{
    this->_autoIndex = rhs._autoIndex ;
    this->_index = rhs._index ;
    this->_allowedMethods = rhs._allowedMethods ;
    this->_return = rhs._return ;
    this->_root = rhs._root ;
    this->_cgiPath = rhs._cgiPath ;
    this->_cgiExtention = rhs._cgiExtention ;
}

Location& Location::operator=( const Location& rhs )
{
    this->_autoIndex = rhs._autoIndex ;
    this->_index = rhs._index ;
    this->_allowedMethods = rhs._allowedMethods ;
    this->_return = rhs._return ;
    this->_root = rhs._root ;
    this->_cgiPath = rhs._cgiPath ;
    this->_cgiExtention = rhs._cgiExtention ;
    return (*this) ;
}

Location::~Location( void )
{

}


const bool&						Location::getAutoIndex( void ) const
{
    return (_autoIndex) ;
}

const std::string&				Location::getIndex( void ) const
{
    return (_index) ;
}

const Location::Methods_t&	Location::getAllowedMethods( void ) const
{
    return (_allowedMethods) ;
}

const std::string&				Location::getReturn( void ) const
{
    return (_return) ;
}

const std::string&				Location::getRoot( void ) const
{
    return (_root) ;
}

const std::string&				Location::getCgiPath( void ) const
{
    return (_cgiPath) ;
}

const std::string&				Location::getCgiExtention( void ) const
{
    return (_cgiExtention) ;
}

void 						Location::setAutoIndex( const bool& _autoIndex )
{
    this->_autoIndex = _autoIndex ;
}

void 						Location::setIndex( const std::string& _index )
{
    this->_index = _index ;
}

void 						Location::setAllowedMethods( const Methods_t& _allowedMethods )
{
    this->_allowedMethods = _allowedMethods ;
}

void 						Location::setReturn( const std::string& _return )
{
    this->_return = _return ;
}

void 						Location::setRoot( const std::string& _root )
{
    this->_root = _root ;
}

void 						Location::setCgiPath( const std::string& _cgiPath )
{
    this->_cgiPath = _cgiPath ;
}

void 						Location::setCgiExtention( const std::string& _cgiExtention )
{
    this->_cgiExtention = _cgiExtention ;
}


static const std::string getMethod( Location::Method_t method )
{
    if (method == Location::GET)
        return ("GET") ;
    if (method == Location::HEAD)
        return ("HEAD") ;
    if (method == Location::POST)
        return ("POST") ;
    if (method == Location::PUT)
        return ("PUT") ;
    if (method == Location::DELETE)
        return ("DELETE") ;
    return ("Error") ;
}

std::ostream& operator<<( std::ostream& os, const Location& location )
{
    os << "AutoIndex: " << (location.getAutoIndex() ? "on" : "off") << std::endl ;
    os << "Index: " << location.getIndex() << std::endl ;
    
    Location::Methods_t methods = location.getAllowedMethods() ;
    Location::Methods_t::iterator it = methods.begin() ;
    os << "AllowedMethods: " ;
    while (it != methods.end())
    {
        os << getMethod(*it++) ;
        if (it != methods.end())
            os << ", " ;
    }
    os << std::endl ;

    os << "Return: " << location.getReturn() << std::endl ;
    os << "Root: " << location.getRoot() << std::endl ;
    os << "CgiPath: " << location.getCgiPath() << std::endl ;
    os << "CgiExtention: " << location.getCgiExtention() << std::endl ;
    return (os) ;
}