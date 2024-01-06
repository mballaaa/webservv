#include "../../includes/parser/Parser.hpp"

Parser::servers_t Parser::servers ;
Lexer::iterator_t Parser::token ;
Lexer::iterator_t Parser::tokenEnd ;

Parser::servers_t Parser::createServers( const Lexer::tokens_t& tokens )
{
    token = tokens.begin() ;
    tokenEnd = tokens.end() ;
    while (token != tokens.end())
    {
        if (accept("server"))
        {
            Server s ;
            accept("{") ;
            while (*token != "}")
            {
                if (accept("listen"))
                    s.setPort(std::atol(token->c_str())) ;
                else if (accept("server_name"))
                    s.setServerName(*token) ;
                else if (accept("host"))
                    s.setHost(*token) ;
                else if (accept("index"))
                {
                    std::cout << "index" << std::endl ;
                    s.setIndex(*token) ;
                }
                else if (accept("root"))
                    s.setRoot(*token) ;
                else if (accept("client_max_body_size"))
                    s.setClientMaxBodySize(std::atol(token->c_str())) ;
                else if (accept("location"))
                {
                    nextSym() ;
                    accept("{") ;
                    while (*token != "}")
                        nextSym() ;
                    accept("{") ;
                }
                else
                    nextSym() ;
            }
            accept("}") ;
            servers.push_back(s) ;
        }
        nextSym() ;
    }
    return (servers) ;
}

Parser::servers_t Parser::parse( Lexer::iterator_t start ) 
{
    (void) start ;
    return (servers) ;
}

void Parser::nextSym( void )
{
    if (token != tokenEnd)
        token++;
}

bool Parser::accept( Lexer::token_t sym, bool increment )
{
    if (*token == sym)
    {
        if (increment)
            nextSym() ;
        return (true) ;
    }
    return (false) ;
}

void Parser::server( Lexer::iterator_t curr )
{
    (void) curr ;
}

void Parser::location( Lexer::iterator_t curr )
{
    (void) curr ;
}
