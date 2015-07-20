#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <string>
#include <vector>
#include <map>

#define DEST_PORT 80

class HttpRequest{
public:
    
    std::string get(std::string url);
    std::string gen_request_line();
    std::string gen_request_header();
    void add_header_fields(std::string k, std::string v);
    std::pair<std::string, std::string> get_host_uri(std::string);
private:
    std::vector<std::string> request_line;
    std::map<std::string, std::string> request_heads;
};

#endif
