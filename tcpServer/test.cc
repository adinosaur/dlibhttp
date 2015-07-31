#include "tcpServer.h"
using namespace std;

const unsigned int PORT = 10000;

int main()
{
    TcpServer tcpServer(PORT);
    tcpServer.run();
    return 0;
}
