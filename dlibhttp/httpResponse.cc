#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "httpResponse.h"

using namespace std;

HttpResponse::HttpResponse(string response)
{
    auto pos1 = response.find("\r\n");
    auto pos2 = response.find("\r\n\r\n", pos1);
    
    response_line = response.substr(0, pos1 + 2);
    response_header = response.substr(pos1 + 2, pos2);
    for (auto i = pos2 + 4; i != response.size(); ++i)
        response_body.push_back(response[i]);
}

string HttpResponse::get_line()
{
    return response_line;
}

string HttpResponse::get_header()
{
    return response_header;
}

string HttpResponse::get_body()
{
    return response_body;
}
