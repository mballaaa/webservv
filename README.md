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

[parse_8cpp_source](https://tgockel.github.io/nginxconfig/parse_8cpp_source.html)

[directives](https://nginx.org/en/docs/http/ngx_http_core_module.html#directives)

[ngx_http_mp4_module](https://nginx.org/en/docs/http/ngx_http_mp4_module.html)

[ngx_http_autoindex_module](https://nginx.org/en/docs/http/ngx_http_autoindex_module.html)

[ngx_http_index_module](https://nginx.org/en/docs/http/ngx_http_index_module.html)

[return](https://nginx.org/en/docs/http/ngx_http_rewrite_module.html#return)

[ngx_http_fastcgi_module](https://nginx.org/en/docs/http/ngx_http_fastcgi_module.html)

[fastcgi_tmp_path](https://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#fastcgi_temp_path)

[google_performance_tool](https://github.com/gperftools/gperftools)

[location](https://nginx.org/en/docs/http/ngx_http_core_module.html#location)

[server](https://nginx.org/en/docs/http/ngx_http_core_module.html#server)

[gzip](https://nginx.org/en/docs/http/ngx_http_gzip_module.html)

[open_file_cache](https://nginx.org/en/docs/http/ngx_http_core_module.html#open_file_cache)

[error_page](https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page)

[single_http_https_server](https://nginx.org/en/docs/http/configuring_https_servers.html#single_http_https_server)

[Resource Exhaustion Attack by SYN Flood with Valid Cookies](https://datatracker.ietf.org/doc/html/rfc7413#section-5.1)

[accf_data](https://man.freebsd.org/cgi/man.cgi?accf_data)

[accf_http](https://man.freebsd.org/cgi/man.cgi?accf_http)

[sockets](https://man7.org/linux/man-pages/man7/socket.7.html)

[client_header_timeout](https://nginx.org/en/docs/http/ngx_http_core_module.html#client_header_timeout)

[keepalive_requests](https://nginx.org/en/docs/http/ngx_http_core_module.html#keepalive_requests)

[Example nginx configuration
](https://nginx.org/en/docs/example.html)
[listen](https://nginx.org/en/docs/http/ngx_http_core_module.html#listen)

[request_processing](https://nginx.org/en/docs/http/request_processing.html)

[root](https://nginx.org/en/docs/http/ngx_http_core_module.html#root)

[events](https://nginx.org/en/docs/events.html#epoll)

[server_name](https://nginx.org/en/docs/http/ngx_http_core_module.html#server_name)

[types](https://nginx.org/en/docs/http/ngx_http_core_module.html#types)

[try_files](https://nginx.org/en/docs/http/ngx_http_core_module.html#try_files)

[merge_slash](https://nginx.org/en/docs/http/ngx_http_core_module.html#merge_slashes)

[ngx_http_api_module](https://nginx.org/en/docs/http/ngx_http_api_module.html)

[admin-guide/web-server](https://docs.nginx.com/nginx/admin-guide/web-server/web-server/)

[Request_methods](https://en.wikipedia.org/wiki/HTTP#Request_methods)

[List_of_HTTP_status_codes](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)

[http-header-line-break-style](https://stackoverflow.com/questions/5757290/http-header-line-break-style)

[designs-example-nonblocking-io-select](https://www.ibm.com/docs/en/i/7.2?topic=designs-example-nonblocking-io-select)

[Getting Started with CGI Programs](http://www.mnuwer.dbasedeveloper.co.uk/dlearn/web/session01.htm)

[nginxconfig Documentation](https://tgockel.github.io/nginxconfig/)

##### cgi

[Environment variables in CGI script
](https://www.ibm.com/docs/en/netcoolomnibus/8.1?topic=scripts-environment-variables-in-cgi-script)

[Scritp_selection](https://datatracker.ietf.org/doc/html/rfc3875#section-3.2)

[cgi_execution](https://datatracker.ietf.org/doc/html/rfc3875#section-3.4)

[Data Length and Buffering Considerations
](https://datatracker.ietf.org/doc/html/rfc3875#section-9.6)