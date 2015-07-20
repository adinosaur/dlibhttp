#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>         //bzero
#include <unistd.h>         //close
#include <sys/types.h>      //recv, send
#include <sys/socket.h>     //recv, send
#include <string>
#include <iostream>
#include "tcp.h"

using namespace std;

#define DEST_PORT 80
const int BUFSIZE = 4096;

TCP::TCP(string server)
{
    sockfd = create_tcp_connect(server);
    cout << "TCP连接成功" << endl;
}

TCP::~TCP()
{
    close(sockfd);
    cout << "TCP连接关闭" << endl;
}

string TCP::get_ip_addr(string host_name)
{
    struct hostent *hp = gethostbyname(host_name.c_str());
    char **pptr = hp->h_addr_list;
    char str[32];
    inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str));
    return str;
}
    
int TCP::create_tcp_connect(string server)
{
    string dest_ip = get_ip_addr(server);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
        
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;                             /* 注意主机字节顺序*/
    dest_addr.sin_port = htons(DEST_PORT);                      /* 远程连接端口, 注意网络字节顺序*/
    dest_addr.sin_addr.s_addr = inet_addr(dest_ip.c_str());     /* 远程 IP 地址, inet_addr() 会返回网络字节顺序*/
    bzero(&(dest_addr.sin_zero), 8);                            /* 其余结构须置 0*/
        
    int res = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in));
    return sock;
}

bool TCP::tcp_send(string m)
{
    ssize_t bytes_sent = send(sockfd, m.c_str(), m.size(), 0);
    return bytes_sent != -1;
}

string TCP::tcp_recv()
{
    string response;
    char buf[BUFSIZE];
    ssize_t bytes_recv;
    while ((bytes_recv = recv(sockfd, buf, sizeof(buf) - 1, 0)) > 0)
    {
        buf[bytes_recv] = '\0';
        //cout << buf << endl;
        response.append(buf);
    }
    return response;
}
