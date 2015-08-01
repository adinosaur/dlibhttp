#include "tcpServer.h"
#include <ext/stdio_filebuf.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

TcpServer::TcpServer(unsigned int _port):port(_port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind_to_socket();
    listen_on_socket();
}

TcpServer::~TcpServer() {
    close(sockfd);
}

void TcpServer::bind_to_socket() {
    const unsigned int HOSTLEN = 256;
    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];

    gethostname(hostname, HOSTLEN);
    hp = gethostbyname(hostname);
    bcopy((void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
    saddr.sin_port = htons(port);
    saddr.sin_family = AF_INET;
    
    if (bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr)) != 0)
        cerr << "bind error" << endl;
}

void TcpServer::listen_on_socket() {
    if (listen(sockfd, 1) != 0)
        cerr << "listen error" << endl;
}

int TcpServer::accept_from_socket() {
    return accept(sockfd, NULL, NULL);
}

void TcpServer::run() {
    while (1) {
        // 刚开始简单地处理请求时阻塞其它请求
        int fd = accept_from_socket();
        __gnu_cxx::stdio_filebuf<char> filebuf1(fd, std::ios::in);
        __gnu_cxx::stdio_filebuf<char> filebuf2(fd, std::ios::out);

        // 对每一次请求都申请一个istream对象和一个ostream对象
        // 效率相对较低，但是不用自己维护IO流的错误
        // 以后可考虑改写此处
        istream is(&filebuf1);
        ostream os(&filebuf2);
        handle(is, os);
    }
}

void TcpServer::handle(istream& is, ostream& os) {
    // virtual
}
