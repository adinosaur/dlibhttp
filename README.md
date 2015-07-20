# dlibhttp
***

###注意事项
使用了c++11的regex，要求g++版本4.9x。编译方式：
```
g++-4.9 --std=c++11 httpRequest.cc tcp.cc main.cc
```

###使用
```
#include <iostream>
#include "httpRequest.h"

using namespace std;

int main()
{
    HttpRequest httpRequest;
    string r = httpRequest.get("http://www.cnblogs.com/kanego/archive/2011/11/10/2244957.html");
    cout << r << endl;
    return 0;
}
```
