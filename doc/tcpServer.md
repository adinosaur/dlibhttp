#tcp服务器

tcp服务器类，使用方法如test.cc文件。

##使用
```
int main()
{
    TcpServer tcpServer(PORT);
    tcpServer.run();
    return 0;
}
```
可以使用telnet调试
```
telnet '127.0.0.1' 10000
```

##编译
```clang++-3.5 -std=c++11 tcpServer.cc test.cc -o tcpServer
```