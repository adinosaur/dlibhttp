#include "tcpServer.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class EchoTcpServer : public TcpServer{
    // 回显TCP服务器
    // 继承了TcPServer，重写handle函数
    // 在handle函数中将从is中读取的单词回显到os中
    public:
        EchoTcpServer(unsigned int port):TcpServer(port) {}
        virtual void handle(std::istream& is, std::ostream& os) {
            string s;
            while (is >> s){
                os << s << endl;
            }
        }
};

int main()
{
    shared_ptr<TcpServer> pTcpServer(new EchoTcpServer(10000));
    pTcpServer->run();
    return 0;
}
