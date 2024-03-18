#ifndef HTTP_REQ
#define HTTP_REQ
#include <iostream>
#include "../Server.hpp"
#include <cerrno>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include "../../includes/Multiplex.hpp"
#include "dirent.h"
#define IS_DIR   0
#define IS_FILE 1
#define IS_RED 2
class Http_req
{
public:
    struct golbal_info
    {
        
    };
    

private:
   /// this the start line 
    std::string req;
    std::string _target;
    
    std ::string method;
    std::string path;
    std ::string http_ver;

   std::map<std::string, std::string> header; 
    Server server;
    Location _loca;
    int byterec;

public:
    void debugFunction();
    Http_req(std::string req,int byterec, Multiplex::listeners_t listenrs);
   void parse_re(std ::string bufer,int bytee);
   int StautRe(std ::string request);
    int MoreValidation();
    void LetGet();
    void CheckLoc();
    ~Http_req();
};

#endif