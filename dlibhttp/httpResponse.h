#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H
#include <string>
#include <vector>

#define DEST_PORT 80

class HttpResponse {
public:
    HttpResponse(const std::string&);
    std::string get_line();
    std::string get_header();
    std::string get_body();
private:
    std::string response_line;
    std::string response_header;
    std::string response_body;
};

#endif
