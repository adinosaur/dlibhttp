#ifndef TCP_H
#define TCP_H
#include <string>

#define DEST_PORT 80

class TCP{
public:
    TCP(std::string);
    ~TCP();
    std::string get_ip_addr(std::string);
    int create_tcp_connect(std::string);
    
    bool tcp_send(std::string);
    std::string tcp_recv();
private:
    int sockfd;
};

#endif
