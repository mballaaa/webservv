#include "../../includes/parser/Parser.hpp"

Parser::servers_t   Parser::servers ;
Parser::setters_t   Parser::setters ;
Lexer::iterator_t   Parser::curr ;
Lexer::iterator_t   Parser::end ;

void Parser::tokenHandle( Server &s )
{
    if (setters.find(*curr) == setters.end())
        throw std::runtime_error("Parser::Unexpected token in handle: " + *curr) ;
    setters[*curr](s) ;
}

void Parser::_server( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("server") ;
    expect("{") ;
    while (*curr != "}")
    {
        tokenHandle(s) ;
    }
    expect("}") ;
    servers.push_back(s) ;
}

void Parser::_listen( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("listen") ;
    s.setPort(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_serverName( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("server_name") ;
    //! consider testing if the server name doesnt end with semicolon
    while (!accept(";"))
    {
        s.appendServerName(*curr++) ;
    }
}

void Parser::_host( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("host") ;
    s.setHost(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_root( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("root") ;
    s.setRoot(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_clientMaxBodySize( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("client_max_body_size") ;
    s.setClientMaxBodySize(std::atol(curr->c_str())) ;
    next() ;
    expect(";") ;
}

void Parser::_index( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("index") ;
    s.setIndex(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_errorPage( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("error_page") ;
    int statusCode = atol(curr->c_str()) ;
    next() ;
    s.appendErrorPage(statusCode, *curr) ;
    next() ;
    expect(";") ;
}

void Parser::_location( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    expect("location") ;
    std::string route(*curr) ;
    next() ;
    expect("{") ;
    Location l = createLocation() ;
    s.appendLocation( route, l ) ;
    expect("}") ;
}

void Parser::_autoIndex( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
}

void Parser::_allowMethods( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
}

void Parser::_return( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
}

void Parser::_cgi( Server& s )
{
    (void) s ;
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
}


Parser::servers_t Parser::parse( const Lexer::tokens_t& tokens )
{
    curr = tokens.begin();
    end = tokens.end() ;
    setters["server"] = _server ;
    setters["listen"] = _listen ;
    setters["server_name"] = _serverName ;
    setters["host"] = _host ;
    setters["root"] = _root ;
    setters["client_max_body_size"] = _clientMaxBodySize ;
    setters["index"] = _index ;
    setters["error_page"] = _errorPage ;
    setters["location"] = _location ;
    setters["autoindex"] = _autoIndex ;
    setters["allow_methods"] = _allowMethods ;
    setters["return"] = _return ;
    setters["root"] = _root ;
    setters["cgi"] = _cgi ;
    while ( curr != end )
    {
        Server s ;
        tokenHandle(s) ;
        // servers.push_back(createServer()) ;
    }
    return (servers) ;
}

bool Parser::accept( const std::string& sym )
{
    if ( sym == *curr )
    {
        next() ;
        return (true) ;
    }
    return (false) ;
}

bool Parser::expect( const std::string& sym )
{
    if ( accept(sym) )
        return (true) ;
    throw std::runtime_error("expected " + sym + " got: " + *curr) ;
    return (false) ;
}

Server Parser::createServer( void )
{
    Server s ;
    while ( next() && *(--curr) != "}" )
    {
        if (accept("listen"))
        {
            s.setPort(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("server_name"))
        {
            while (!accept(";"))
            {
                s.appendServerName(*curr++) ;
            }
        }
        else if (accept("host"))
        {
            s.setHost(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("root"))
        {
            s.setRoot(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("client_max_body_size"))
        {
            s.setClientMaxBodySize(std::atol(curr->c_str())) ;
            next() ;
            expect(";") ;
        }
        else if (accept("index"))
        {
            s.setIndex(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("error_page"))
        {
            int statusCode = atol(curr->c_str()) ;
            next() ;
            s.appendErrorPage(statusCode, *curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("location"))
        {
            std::string route(*curr) ;
            next() ;
            expect("{") ;
            Location l = createLocation() ;
            s.appendLocation( route, l ) ;
            expect("}") ;
        }
        else 
            throw std::runtime_error("Unexpected token: in server" + *curr) ;
    }
    return (s) ;
}

Location Parser::createLocation( void )
{
    Location l ;
    while ( next() && *(--curr) != "}" )
    {
        if (accept("allow_methods"))
        {
            Location::Methods_t methods ;
            while (!accept(";"))
            {
                if (*curr == "GET")
                    methods.push_back(Location::GET) ;
                else if (*curr == "POST")
                    methods.push_back(Location::POST) ;
                else if (*curr == "DELETE")
                    methods.push_back(Location::DELETE) ;
                else
                    throw std::runtime_error("UnAutorized method: " + *curr) ;
                next() ;
            }
            l.setAllowedMethods(methods) ;
        }
        else if (accept("autoindex"))
        {
            l.setAutoIndex(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("root"))
        {
            l.setRoot(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("index"))
        {
            l.setIndex(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("cgi"))
        {
            l.setCgi(*curr) ;
            next() ;
            expect(";") ;
        }
        else if (accept("return"))
        {
            l.setReturn(*curr) ;
            next() ;
            expect(";") ;
        }
        else 
            throw std::runtime_error("Unexpected token: in location " + *curr) ;
    }
    return (l) ;
}

bool Parser::next( void )
{
    if (curr != end)
    {
        curr++ ;
        return (true) ;
    }
    return (false) ;
}