#include "../../includes/Request/Http_req.hpp"
#include <unistd.h>

Http_req::Http_req() {
    state = START;
}

Http_req::Http_req(std ::string req, int byterec, std::map<int, Server> listners)
{

    // std :: cerr << s.getClientMaxBodySize();

    //  std::map<SOCKET,Server> ::iterator it;

    // for (it =listners.begin() ;it !=listners.end();++it)

    // {

    //     std ::cerr << "********* here***********\n";
    //     std :: cerr << it->second.getClientMaxBodySize() << std ::endl;
    //     std ::cerr << "********* here***********\n";
    std::map<int, Server>::iterator it;

    it = listners.begin();

    this->req = req;
    this->byterec = byterec;
    this->server = it->second;
   // std :: cerr << "====>root"  << server.getRoot() << std ::endl;
   /// See location

//    std :: cerr << "Yessss\n";
//    std::map<std::string ,Location> getLocation=server.getLocations();
//         std ::cerr << "==>\n" ;
//    std::map<std::string, Location>::iterator it_loc;
//     for (it_loc = getLocation.begin(); it_loc != getLocation.end(); ++it_loc) {
//     std :: cerr << it_loc->first << std ::endl;
// }
    // for(it_loc = getLocation.begin();it_loc !=getLocation.end();++it_loc)
    // {
    //     std :: cerr << " =>" << it_loc->first << std ::endl;
    // }
    // parse_re(req, byterec); // amine: I commented this line

}

// copyy
Http_req& Http_req::operator=(const Http_req &obj)
{
    if (this != &obj) {

        req = obj.req;
        _target = obj._target;
        method = obj.method;
        path = obj.path;
        http_ver = obj.http_ver;
        header = obj.header;
        server = obj.server;
        _loca = obj._loca;
        byterec = obj.byterec;
    }
    return *this;
}
/*  Getter   */
const std::string& Http_req::getTarget() const {
    return _target;
}
const std::string& Http_req::getBody() const {
    return body;
}

const std::string& Http_req::getMethod() const {
    return method;
}

const std::string& Http_req::getPath() const {
    return path;
}

const std::string& Http_req::getHttpVersion() const {
    return http_ver;
}

const std::map<std::string, std::string>& Http_req::getHeader() const {
    return header;
}

const Server& Http_req::getServer() const {
    return server;
}

const Location& Http_req::getLocation() const {
    return _loca;
}
/*
    structure of request
        ===> start line
        Type(Methode) +Request target
        + HTTP version

        *****2Header

*/
bool is_same(std::string key,std::string target)
{
    //key is valuee from config location
    // //target ==is path request
    // std :: cerr << " key from conf===> " << key << std ::endl;
    // std :: cerr << "path==>"  << target << std :: endl;
    if(target.length() < key.length())
    {
     //   std :: cerr << "JJJJ\n";

        return false;
    }
    int value = target.compare(0,key.length(),key);

   return (value==0);

}
int check_path(std ::string path)
{

    if (path.empty())
    {
        return (0);
    }
    if (path.at(0) != '/')
    {
        return (0);
    }

    return (1);
}
std::string to_stringmetohd(int value) {
    switch (value) {
        case 0: return "GET";
        case 2: return "POST";
        case 4: return "DELETE";
        default: return "Unknown Method";
    }
}
std ::string SetRootLoc(std ::string path,std ::string loac_value,std ::string root)
{
    std ::string result;
    std :: cerr << "==> path:" << path << std ::endl;
	std :: cerr << "==>locationpath:" << loac_value << std ::endl;
	std :: cerr << "==>root:" << root << std ::endl;
    size_t it =path.find(loac_value);

    if(it != std ::string::npos )
    {

        if (path[path.size() - 1] != '/')
{
    path += "/";
}

        path.replace(it,loac_value.length(),root+loac_value);
        return path;
    }
    return path;
}
int Http_req::MoreValidation()
{


    if (!check_path(this->path))
    {

        return 0;
    }
    /// check method


    if (method != "GET" && method != "POST" && method != "DELETE")
    {

        return (0);
    }
    if (http_ver != "HTTP/1.1")
    {

        return (0);
    }

    // get    max body size  in conf
    size_t maxx_size = this->server.getClientMaxBodySize();
    char *endptr;
     size_t content_len;
    if(header.find("content-length")!=header.end())
    {
     content_len  = strtol(header["content-length"].c_str(), &endptr, 10);
    if (endptr == header["content-length"].c_str())
    {
        std::cerr << "Error: Invalid content-length in request." << std::endl;
        return 0;
    }

    if( maxx_size < content_len)
                return (0);

    }
    if(header.find("transfer-encoding")!=header.end() && header["transfer-encoding"]!="chunked")
        return (0);
    if(method=="POST"  && header.find("content-length")==header.end() && header.find("transfer-encoding")==header.end())
        return (0);

    this->_target=this->path;
    // now let check if match or not
    std::map<std ::string,Location> location=this->server.getLocations();
    std::map<std::string,Location> :: iterator it;
    int flag=0;
    std ::string key ;
    for ( it =location.begin() ; it != location.end(); it++)
    {

         key =it->first;

         if(is_same(key,_target))
         {
           // std :: cerr << "is same\n" << std ::endl;
             flag++;
             this->_loca=it->second;
              break;
        }

    }

    if(flag==0)
    {
        std :: cerr << "Not Match \n";
        // if not found any match
      return (0); /// No match akhouuya
    }



    ///std :: cerr << "weech\n";
     Location::redirection_t  red=this->_loca.getReturn();
    //  std :: cerr << red.first << std ::endl;
    //  std :: cerr << red.second << std ::endl;
    if(red.first !=0 && red.second != "")
    {
        this->_target=red.second;
        return 0;
        //std :: cerr << "tis the path\n" << path << std ::endl;
    }
    // let check allow methode
    Location::Methods_t allowmethod=this->_loca.getAllowedMethods();
    bool is_exit=false;
    (void) is_exit;

   for(size_t i =0 ; i < allowmethod.size();i++)
   {
        // change to stirng
        std ::string get_methode=to_stringmetohd(allowmethod[i]);
      //  std :: cerr << "get methode==>\n" << get_methode << std ::endl;
        if(get_methode==this->method)
        {

            is_exit=true;
            break;
        }


   }
    /// TO DO SHLOUD DO SOMETHING IF ALLOW MEHODE FALSE


    _target=SetRootLoc(_target,key,this->server.getRoot());
    std :: cerr <<"last =>" <<  _target << std :: endl;

    return (1);
}
void Http_req::debugFunction()
{
    std ::cerr << "our infoo\n";
    std ::cerr << "type mthode=>" << this->method << std ::endl;
    std ::cerr << "path=>" << this->path << std ::endl;
    std ::cerr << "vers=>" << this->http_ver << std ::endl;

    ///// print headar
    std::map<std::string, std::string>::iterator it;
    for (it = header.begin(); it != header.end(); it++)
    {
        if (it->first == "Content-Length")
        {
            std ::cerr << "ssssss\n";
        }
        //std ::cerr << it->first << ":" << it->second << std ::endl;
    }
}
int Http_req::StautRe(std::string request)
{
    int res;
    res = 0;
    size_t len_req = request.find("\r\n\r\n");
    if (len_req == std::string::npos)
    {
        // perror("Error : RequstHeader ==>Finding end of request ");
        if (state == START)
            state = HEADER ;
        return (0);
    }
    body=request.substr(len_req+4);
    //std :: cerr << "this body ==>"  <<body << std ::endl;


    std::istringstream input(request);
    input >> this->method >> this->path >> this->http_ver;

    std ::string next_line;
    std ::getline(input, next_line);

    while (std::getline(input, next_line, '\n') && next_line != "\r")
    {
        // try to supp all \r in each line we have
        std::string::iterator new_end = std::remove(next_line.begin(), next_line.end(), '\r');
        int distance = std::distance(next_line.begin(), new_end);
        next_line.resize(distance);
        size_t find = next_line.find(":");
        if (find != std::string ::npos)
        {
            std ::string key = next_line.substr(0, find);
            std ::string value = next_line.substr(find + 1, distance);
            for (size_t i = 0; i < key.length(); i++)
            {
                key[i] = std::tolower(key[i]);
            }
            if (header.find(key) != header.end())
            {
                perror("Error : RequstHeader ==>Duplcated");
                return (0);
            }
            header[key] = value;

            /// debug function
        }
      //  std :: cerr << "===>" << next_line << std ::endl;
    }

    //======> check path
    if (MoreValidation())
    {

    }
      //debugFunction();

    res = 1;
    return (res);
}
void Http_req::parse_re(std ::string bufer, int bytee)
{
    (void)bufer;
    (void)bytee;
    if (!StautRe(bufer) || bytee < 0)
    {

    }
    else
    {
        if(method=="GET")
        {
            LetGet();
        }

    }
}

bool Is_dir(const char *ptr)
{
    std :: cerr << "ptr==>" << ptr << std ::endl;
   if(!access(ptr,X_OK |R_OK))
   {
    DIR *dir= opendir(ptr);
    if(dir !=NULL)
    {
        std :: cerr << "Is directory\n";
        return true;
    }
    return false;
   }
   else
   {
    return false;
   }


}
int is_file_dir(std::string uri)
{
    if(Is_dir(uri.c_str()))
        return 0;
    return 1;
}

void Http_req ::CheckLoc()
{


    if(this->_loca.getIndex().size()!=0)
    {

        std ::vector<std ::string> index=this->_loca.getIndex();
        //check if index file are exit
        /// ==> get first index string
        std ::string main_index=index.at(0);
        std :: cerr << "index  name==>" << main_index << std :: endl;
        _target+=main_index;
        std :: cerr << _target << std ::endl;


    }


}
// =====> Let Start Get
void Http_req:: LetGet()
{
    std ::string URI=this->_target;
    int check_type=is_file_dir(URI);
   // std :: cerr << "output" << check_type << std ::endl;
    if(check_type == IS_DIR)
    {
        std :: cerr << "hEYY\n";
       CheckLoc();
    }

}
Http_req::~Http_req()
{
}
