#include "../includes/Location.hpp"

Location::Location( void ) : _autoIndex(false), _index(""), _allowedMethods(), _return(), _root(""), _cgi(false)
{
}

Location::Location( const Location& rhs )
{
    this->_autoIndex = rhs._autoIndex ;
    this->_index = rhs._index ;
    this->_allowedMethods = rhs._allowedMethods ;
    this->_return = rhs._return ;
    this->_root = rhs._root ;
    this->_cgi = rhs._cgi ;
}

Location& Location::operator=( const Location& rhs )
{
    this->_autoIndex = rhs._autoIndex ;
    this->_index = rhs._index ;
    this->_allowedMethods = rhs._allowedMethods ;
    this->_return = rhs._return ;
    this->_root = rhs._root ;
    this->_cgi = rhs._cgi ;

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

const bool&                   Location::getCgi( void ) const
{
    return (_cgi ) ;
}

void 						Location::setAutoIndex( const std::string& _autoIndex )
{
    if (_autoIndex == "on")
        this->_autoIndex = true ;
    else if (_autoIndex == "off")
        this->_autoIndex = false ;
    else
        throw std::runtime_error("Unexpected value for autoindex: " + _autoIndex) ;
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

void 						Location::setCgi( const std::string& state )
{
    if (state == "on")
        this->_cgi = true ;
    else if (state == "off")
        this->_cgi = false ;
    else
        throw std::runtime_error("Unexpected value for cgi: " + state) ;
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
    Location::Methods_t::iterator itMethod = methods.begin() ;
    os << "AllowedMethods: " ;
    while (itMethod != methods.end())
    {
        os << getMethod(*itMethod++) ;
        if (itMethod != methods.end())
            os << ", " ;
    }
    os << std::endl ;

    os << "Return: " << location.getReturn() << std::endl ;
    os << "Root: " << location.getRoot() << std::endl ;
    os << "cgi: " << (location.getCgi() ? "on" : "off") << std::endl ;

    return (os) ;
}