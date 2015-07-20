#include <string>
#include <iostream>
#include <regex>
#include "tcp.h"
#include "httpRequest.h"

using namespace std;


string HttpRequest::gen_request_line()
{
    string r;
    r.append(request_line[0]);
    for (vector<string>::size_type i = 1; i != request_line.size(); ++i)
    {
        r.append(" ");
        r.append(request_line[i]);
    }
    return r;
}

string HttpRequest::gen_request_header()
{
    string r;
    map<string, string>::iterator beg = request_heads.begin();
    map<string, string>::iterator end = request_heads.end();
    
    for ( ;beg != end; ++beg)
    {
        r.append(beg->first + ": " + beg->second + "\r\n");
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
    pair<std::string, std::string> p = get_host_uri(url);
    string host = p.first;
    string uri = p.second;
    
    /* 构造请求 */
    string request;
    
    request_line.push_back("GET");
    request_line.push_back(uri);
    request_line.push_back("HTTP/1.1");
    request_line.push_back("\r\n");
    request.append(gen_request_line());
    
    add_header_fields("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36");
    add_header_fields("Host", host);
    add_header_fields("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    request.append(gen_request_header());
    
    cout << request << endl;
    /* TCP连接 */
    TCP tcp(host);
    
    /* 发送请求 */
    tcp.tcp_send(request);
    
    /* 接收响应 */
    return tcp.tcp_recv();
}
