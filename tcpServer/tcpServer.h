#ifndef TCPSERVER
#define TCPSERVER

class TcpServer{
    public:
        TcpServer(unsigned int);
        ~TcpServer();
        
        void run();
        void handle(std::istream&, std::ostream&);
    private:
        void bind_to_socket();
        void listen_on_socket();
        int accept_from_socket();
        
        unsigned int port;
        int sockfd;
};

#endif
