# webserv
A HTTP server in C++ 98

## resources:

[Recursive descent parser](https://en.wikipedia.org/wiki/Recursive_descent_parser)

[Kaydooo Webserv_42](https://github.com/Kaydooo/Webserv_42)
[http server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)

HTTP/1.1 →Initially it is [RFC 2616](https://www.rfc-editor.org/info/rfc2616) but later replaced by [RFC 7230](https://www.rfc-editor.org/info/rfc7230), [RFC 7231](https://www.rfc-editor.org/info/rfc7231), [RFC 7232](https://www.rfc-editor.org/info/rfc7232), [RFC 7233](https://www.rfc-editor.org/info/rfc7233), [RFC 7234](https://www.rfc-editor.org/info/rfc7234), [RFC 7235](https://www.rfc-editor.org/info/rfc7235). So, we need to read from [RFC 7230](https://www.rfc-editor.org/info/rfc7230) to [RFC 7235](https://www.rfc-editor.org/info/rfc7235) to implement basic workings of HTTP.

[What does multiplexing mean in HTTP/2?](https://stackoverflow.com/a/36519379/10565493)

[HTTP2 Multiplexing: The devil is in the details](https://blog.codavel.com/http2-multiplexing)

[4.2 Server Architectures](https://berb.github.io/diploma-thesis/original/042_serverarch.html)

```c++
struct epoll_event {
    uint32_t      events;  /* Epoll events */
    epoll_data_t  data;    /* User data variable */
};

union epoll_data {
    void     *ptr;
    int       fd;
    uint32_t  u32;
    uint64_t  u64;
};

typedef union epoll_data  epoll_data_t;
```

[io multiplexing select poll epoll in linux](https://www.softprayog.in/programming/io-multiplexing-select-poll-epoll-in-linux)


## Exportable constants

source [metacpan.org](https://metacpan.org/pod/IO::Epoll)

### Exported by default:

```c++
EPOLLERR
EPOLLET
EPOLLHUP
EPOLLIN
EPOLLMSG
EPOLLOUT
EPOLLPRI
EPOLLRDBAND
EPOLLRDNORM
EPOLLWRBAND
EPOLLWRNORM
EPOLL_CTL_ADD
EPOLL_CTL_DEL
EPOLL_CTL_MOD
```
### Exported by the :compat tag:

```
POLLNVAL
POLLIN
POLLOUT
POLLERR
POLLHUP
POLLPRI
POLLRDNORM
POLLWRNORM
POLLRDBAND
POLLWRBAND
```

[epoll in 3 easy steps](https://suchprogramming.com/epoll-in-3-easy-steps/)