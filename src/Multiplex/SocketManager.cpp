#include "../../includes/SocketManager.hpp"

int SocketManager::epollFD = -1 ;

int SocketManager::createSocket( const char *port, int ai_family, int ai_socktype, int ai_flags)
{
    struct addrinfo hints ;
    struct addrinfo *result, *rp ;
    int s, sfd ;

    bzero(&hints, sizeof(struct addrinfo)) ;
    hints.ai_family = ai_family ;
    hints.ai_socktype = ai_socktype ;
    hints.ai_flags = ai_flags ;

    s = getaddrinfo(NULL, port, &hints, &result) ;
    if (s != 0)
    {
        perror("getaddrinfo") ;
        throw std::runtime_error("getaddrinfo") ;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol) ;
        if (sfd == -1)
            continue ;
        s = bind(sfd, rp->ai_addr, rp->ai_addrlen) ;
        if (s == 0)
        {
            /* We managed to bind successfully! */
            break ;
        }
        close(sfd) ;
    }
    if (rp == NULL)
    {
        fprintf(stderr, "Could not bind\n") ;
        throw std::runtime_error("Could not bind") ;
        return -1 ;
    }
    freeaddrinfo(result) ;
    return sfd;
}

int SocketManager::makeSocketNonBlocking( int sfd )
{
    int flags ;

    flags = fcntl(sfd, F_GETFL, 0) ;
    if (flags == -1)
    {
        perror("fcntl") ;
        throw std::runtime_error("Could not get socket flags") ;
        return -1 ;
    }

    flags |= O_NONBLOCK ;
    flags = fcntl(sfd, F_SETFL, flags) ;
    if (flags == -1)
    {
        perror("fcntl") ;
        throw std::runtime_error("Could not set socket flags") ;
        return -1 ;
    }
    return 0 ;
}

int SocketManager::startListening( int sfd )
{
    int s ;
    s = listen (sfd, SOMAXCONN);
    if (s == -1)
    {
        perror ("listen");
        throw std::runtime_error("Could not listen on socket") ;
        return -1 ;
    }
    return 0 ;
}

int SocketManager::createEpoll()
{
    epollFD = epoll_create1 (0);
    if (epollFD == -1)
    {
        perror ("epoll_create");
        throw std::runtime_error("Could not create epoll") ;
        return -1 ;
    }

    return epollFD ;
}

int SocketManager::epollAddSocket( int sfd )
{
    int s ;
    struct epoll_event event;

    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET;
    s = epoll_ctl (epollFD, EPOLL_CTL_ADD, sfd, &event);
    if (s == -1)
    {
        perror ("epoll_ctl");
        throw std::runtime_error("Could not create epoll") ;
        return -1 ;
    }
    return 0 ;
}