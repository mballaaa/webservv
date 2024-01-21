#include "../../includes/Multiplex.hpp"
#include "../../includes/Request/Request.hpp"

Multiplex::servers_t Multiplex::servers ;

void Multiplex::setServers( const servers_t& _servers )
{
    servers_t::const_iterator it = _servers.begin() ;
    while (it != _servers.end())
        servers.push_back(*it++) ;
    
}

void Multiplex::setup( const Server& server )
{
    (void)server ;
    // int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0) ;
    // if (fd < 0)
    // {
    //     perror("socket failed") ;
    //     throw std::runtime_error("socket() failed successfully") ;
    // }
    // std::cout << "Socket open successfully" << std::endl ;

    // sockaddr_in sockaddr ;
    // sockaddr.sin_family = AF_INET ;
    // sockaddr.sin_addr.s_addr = INADDR_ANY ;
    // sockaddr.sin_port = htons(server.getPort()) ;

    // if (bind(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    // {
    //     perror("bind failed") ;
    //     close(fd) ;
    //     throw std::runtime_error("bind() failed successfully") ;
    // }
    // std::cout << "Socket bouned successfully" << std::endl ;
}

void Multiplex::start( void )
{
    int sfd, s, efd;
    std::map<int, Server> listeningSockets ;
    std::map<int, Request> requests ;
    struct epoll_event events[SOMAXCONN];

    if (servers.empty())
    {
        throw std::runtime_error("Servers are not set") ;
        return ;
    }
    servers_t::iterator servIt = servers.begin() ;
    // each server should have a socket
    efd = SocketManager::createEpoll() ;
    while (servIt != servers.end())
    {
        std::cout << "Listening on: " << servIt->getHost() << ":" << servIt->getPort() << "..." << std::endl ;
        sfd = SocketManager::createSocket(servIt->getHost().c_str(), servIt->getPort().c_str(), AF_INET, SOCK_STREAM, AI_PASSIVE) ;
        SocketManager::makeSocketNonBlocking (sfd);
        SocketManager::startListening(sfd) ;
        SocketManager::epollCtlSocket(sfd, EPOLL_CTL_ADD) ;
        listeningSockets[sfd] = *servIt ;
        servIt++ ;
    }

    std::map<int, std::string> eventName ;

    eventName[EPOLLIN] = "EPOLLIN" ;
    eventName[EPOLLET] = "EPOLLET" ;
    eventName[EPOLLOUT] = "EPOLLOUT" ;
    eventName[EPOLLERR] = "EPOLLERR" ;
    eventName[EPOLLHUP] = "EPOLLHUP" ;
    /* The event loop */
    while (1)
    {
        int eventCount, i;

        eventCount = epoll_wait (efd, events, SOMAXCONN, -1);
        std::cout << eventCount << " events ready" << std::endl ;
        for (i = 0; i < eventCount; i++)
        {
            std::cout << "descriptor " << events[i].data.fd << " " ;
            if (events[i].events & EPOLLOUT)
                std::cout << eventName[EPOLLOUT] ;
            if (events[i].events & EPOLLIN)
                std::cout << eventName[EPOLLIN] ;
            if (events[i].events & EPOLLET)
                std::cout << eventName[EPOLLET] ;
            if (events[i].events & EPOLLERR)
                std::cout << eventName[EPOLLERR] ;
            if (events[i].events & EPOLLHUP)
                std::cout << eventName[EPOLLHUP] ;
            std::cout << std::endl ;

            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP))
            {
                /* An error has occured on this fd, or the socket is not
                    ready for reading (why were we notified then?) */
                fprintf (stderr, "epoll error\n");
                close (events[i].data.fd);
                perror("EPOLLERR | EPOLLHUP") ;
                continue;
            }
            else if (listeningSockets.find(events[i].data.fd) != listeningSockets.end())
            {
                /* We have a notification on the listening socket, which
                    means one or more incoming connections. */
                struct sockaddr in_addr;
                socklen_t in_len;
                int infd;
                char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                in_len = sizeof in_addr;
                infd = accept (events[i].data.fd, &in_addr, &in_len);
                if (!ISVALIDSOCKET(infd))
                {
                    if ((errno == EAGAIN) ||
                        (errno == EWOULDBLOCK))
                    {
                        /* We have processed all incoming
                            connections. */
                        continue ;
                    }
                    else
                    {
                        perror ("accept");
                        continue ;
                    }
                }
                
                s = getnameinfo (&in_addr, in_len,
                                hbuf, sizeof hbuf,
                                sbuf, sizeof sbuf,
                                NI_NUMERICHOST | NI_NUMERICSERV);
                if (s == 0)
                {
                    printf("Accepted connection on descriptor %d "
                            "(host=%s, port=%s)\n", infd, hbuf, sbuf);
                }

                /* Make the incoming socket non-blocking and add it to the
                    list of fds to monitor. */
                SocketManager::makeSocketNonBlocking(infd);
                SocketManager::epollCtlSocket(infd, EPOLL_CTL_ADD) ;
                requests.insert(std::make_pair(infd, Request(infd, listeningSockets[events[i].data.fd], in_addr))) ;
                continue;
            }
            else if (events[i].events & EPOLLIN)
            {
                ssize_t bytesReceived;
                char buf[R_SIZE] = {0};

                bytesReceived = read (events[i].data.fd, buf, sizeof(char) * R_SIZE - 1);
                if (bytesReceived == -1)
                {
                    perror ("read");
                    printf ("Closed connection on descriptor %d\n",
                    events[i].data.fd);

                    /* Closing the descriptor will make epoll remove it
                        from the set of descriptors which are monitored. */
                    close (events[i].data.fd);
                    requests.erase(events[i].data.fd) ;
                    continue ;
                }
                else if (bytesReceived == 0)
                {
                    /* End of file. The remote has closed the
                        connection. */
                    printf ("Closed connection on descriptor %d by client\n",
                    events[i].data.fd);

                    /* Closing the descriptor will make epoll remove it
                        from the set of descriptors which are monitored. */
                    close (events[i].data.fd);
                    requests.erase(events[i].data.fd) ;
                    continue ;
                }
                requests.find(events[i].data.fd)->second.request += buf ;
                /* Write the buffer to standard output */
                std::cout << FOREGRN ;
                std::cout << "============== Request ==============" << std::endl ;
                std::cout << "==============+++++++++==============" << std::endl ;
                s = write (1, buf, bytesReceived);
                std::cout << "==============+++++++++==============" << std::endl ;
                std::cout << "==============+++++++++==============" << std::endl ;
                std::cout << RESETTEXT ;
                if (s == -1)
                {
                    perror ("write");
                    throw std::runtime_error("Could not write in ") ;
                }

                /**
                 * Set associated socket to EPOLLOUT to write reponse in the next iteration
                */
                if (requests.find(events[i].data.fd)->second.request.find("\r\n\r\n") != std::string::npos)
                    SocketManager::epollCtlSocket(events[i].data.fd, EPOLL_CTL_MOD, EPOLLOUT) ;
            }
            else if (events[i].events & EPOLLOUT)
            {
                SocketManager::epollCtlSocket(events[i].data.fd, EPOLL_CTL_MOD, EPOLLIN) ;
                std::string response("HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/html\r\n\r\nHello World!\n") ;
                s = write (events[i].data.fd, response.c_str(), response.size());
                if (s == -1)
                    throw std::runtime_error("Cant write response") ;
                std::cout << FOREBLU ;
                std::cout << "============== Response ==============" << std::endl ;
                std::cout << "==============++++++++++==============" << std::endl ;
                write (1, response.c_str(), response.size());
                std::cout << "==============+++++++++==============" << std::endl ;
                std::cout << "==============+++++++++==============" << std::endl ;
                std::cout << RESETTEXT ;
                if (requests.find(events[i].data.fd)->second.request.find("Connection: close") != std::string::npos)
                {
                    printf ("Closed connection on descriptor %d\n",
                            events[i].data.fd);
                    /* Closing the descriptor will make epoll remove it
                        from the set of descriptors which are monitored. */
                    close (events[i].data.fd);
                    // requests.erase(events[i].data.fd) ;
                }
                requests.find(events[i].data.fd)->second.request.clear() ;
                std::cout << "Response Sent" << std::endl ;
            }
        }
    }
    close (sfd);
}
