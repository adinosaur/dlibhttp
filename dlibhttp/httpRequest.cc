#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "tcp.h"
#include "httpRequest.h"

using namespace std;


string HttpRequest::gen_request_header()
{
    string r;
    for ( auto it : request_heads)
    {
        r.append(it.first + ": " + it.second + "\r\n");
    }
    r.append("\r\n");
    return r;
}

void HttpRequest::add_header_fields(std::string k, std::string v)
{
    request_heads.insert(make_pair(k, v));
}

pair<std::string, std::string> HttpRequest::get_host_uri(string url)
{
    regex pattern("http://(.*?)(/.*)");
    smatch mat;
    if(!regex_search(url, mat, pattern) && mat.size() != 3)
        throw runtime_error("wrong url");
    return make_pair(mat[1], mat[2]);
}

string HttpRequest::get(string url)
{
    auto p = get_host_uri(url);
    string host = p.first;
    string uri = p.second;
    
    add_header_fields("Host", host);
    
    /* 构造请求 */
    string request;
    ostringstream ss;
    
    /* request line */
    ss << "GET " << uri << " HTTP/1.1\r\n";
    request = ss.str();
    request.append(gen_request_header());
    cout << request;
    
    /* TCP连接 */
    TCP tcp(host);
    
    /* 发送请求 */
    tcp.tcp_send(request);
    
    /* 接收响应 */
    return tcp.tcp_recv();
}
