#TcpServer

##简介
tcp服务器类，使用方法如test.cc文件。

##编译
```
clang++-3.5 -std=c++11 tcpServer.cc test.cc -o tcpServer
```

##使用
```
class EchoTcpServer : public TcpServer{
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
```
可以使用telnet调试
```
telnet '127.0.0.1' 10000
```

