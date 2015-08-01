#ifndef TCPSERVER
#define TCPSERVER
#include <iostream>

class TcpServer{
    // 每一个TcpServer对应于1个唯一的socket
    // 因此不允许多个TcpServer的对象保存相同的socket
    // 禁止了拷贝构造函数、赋值运算函数
    public:
        explicit TcpServer(unsigned int);
        TcpServer(const TcpServer&) = delete;
        TcpServer& operator=(const TcpServer&) = delete;
        virtual ~TcpServer();
        
        void run();
        
        //派生类重写handle函数
        virtual void handle(std::istream&, std::ostream&);
    private:
        void bind_to_socket();
        void listen_on_socket();
        int accept_from_socket();
       
        unsigned int port;
        int sockfd;
};

#endif
