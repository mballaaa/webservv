#include "../../includes/Multiplex.hpp"

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

#define READ_SIZE 1024

void Multiplex::start( void )
{
    int sfd, s, efd;
    std::vector<int> listeningSockets ;
    struct epoll_event *events;


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
        sfd = SocketManager::createSocket(servIt->getHost().c_str(), servIt->getPort().c_str()) ;
        SocketManager::makeSocketNonBlocking (sfd);
        SocketManager::startListening(sfd) ;
        SocketManager::epollAddSocket(sfd) ;
        listeningSockets.push_back(sfd) ;
        servIt++ ;
    }

    /* Buffer where events are returned */
    events = (epoll_event*)calloc (SOMAXCONN, sizeof(struct epoll_event));

    /* The event loop */
    while (1)
    {
        int eventCount, i;

        eventCount = epoll_wait (efd, events, SOMAXCONN, -1);
        std::cout << eventCount << " events ready" << std::endl ;
        for (i = 0; i < eventCount; i++)
        {
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN)))
            {
                /* An error has occured on this fd, or the socket is not
                    ready for reading (why were we notified then?) */
                fprintf (stderr, "epoll error\n");
                close (events[i].data.fd);
                continue;
            }
            else if (std::find(listeningSockets.begin(), listeningSockets.end(), events[i].data.fd) != listeningSockets.end())
            {
                /* We have a notification on the listening socket, which
                    means one or more incoming connections. */
                while (1)
                {
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                    in_len = sizeof in_addr;
                    infd = accept (events[i].data.fd, &in_addr, &in_len);
                    if (infd == -1)
                    {
                        if ((errno == EAGAIN) ||
                            (errno == EWOULDBLOCK))
                        {
                            /* We have processed all incoming
                                connections. */
                            break;
                        }
                        else
                        {
                            perror ("accept");
                            break;
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
                    s = SocketManager::makeSocketNonBlocking(infd);
                    if (s == -1)
                        abort ();

                    SocketManager::epollAddSocket(infd) ;
                }
                continue;
            }
            else if (events[i].events & EPOLLIN)
            {
                /* We have data on the fd waiting to be read. Read and
                    display it. We must read whatever data is available
                    completely, as we are running in edge-triggered mode
                    and won't get a notification again for the same
                    data. */
                int done = 0;

                while (1)
                {
                    ssize_t count;
                    char buf[512];

                    count = read (events[i].data.fd, buf, sizeof buf);
                    if (count == -1)
                    {
                        /* If errno == EAGAIN, that means we have read all
                            data. So go back to the main loop. */
                        if (errno != EAGAIN)
                        {
                            perror ("read");
                            done = 1;
                        }
                        break;
                    }
                    else if (count == 0)
                    {
                        /* End of file. The remote has closed the
                            connection. */
                        done = 1;
                        break;
                    }

                    std::string response("HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/html\r\n\r\nHello World!\n") ;
                    s = write (events[i].data.fd, response.c_str(), response.size());
                    if (s == -1)
                        std::cout << "Cant write response" << std::endl ;
                    /* Write the buffer to standard output */
                    s = write (1, buf, count);
                    if (s == -1)
                    {
                        perror ("write");
                        abort ();
                    }
                }
                if (done)
                {
                    printf ("Closed connection on descriptor %d\n",
                            events[i].data.fd);
                    /* Closing the descriptor will make epoll remove it
                        from the set of descriptors which are monitored. */
                    close (events[i].data.fd);
                }
            }
        }
    }

    free (events);

    close (sfd);

}
