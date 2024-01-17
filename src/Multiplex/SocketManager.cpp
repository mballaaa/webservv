#include "../../includes/SocketManager.hpp"

int SocketManager::createSocket( const char *port, int ai_family, int ai_socktype, int ai_flags)
{
    struct addrinfo hints ;
    struct addrinfo *result, *rp ;
    int s, sfd ;

    bzero(&hints, sizeof(struct addrinfo)) ;
    hints.ai_family = AF_UNSPEC ;
    hints.ai_socktype = SOCK_STREAM ;
    hints.ai_flags = AI_PASSIVE ;

    s = getaddrinfo(NULL, port, &hints, &result) ;
    if (s != 0)
    {
        perror("getaddrinfo") ;
        throw std::runtime_error("getaddrinfo") ;
    }

    
}