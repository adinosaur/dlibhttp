# dlibhttp
***

### 简介
c++的http库，未完待续。

### 注意事项
使用了c++11的regex，要求g++版本4.9x。编译方式：
```
g++-4.9 --std=c++11 httpRequest.cc tcp.cc main.cc
```

### 使用
```
#include <iostream>
#include <fstream>
#include <vector>
#include "httpRequest.h"
#include "httpResponse.h"

using namespace std;

int main()
{
    auto url = "http://m1.music.126.net/g2FkLiGHZg6MnXdQ4xmPSA==/7857110092282670.mp3";

    HttpRequest httpRequest;
    httpRequest.add_header_fields("Accept", "*/*");
    httpRequest.add_header_fields("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36");
    string r = httpRequest.get(url);
    
    HttpResponse httpResponse(r);
    
    cout << httpResponse.get_line();
    cout << httpResponse.get_header();
    string body = httpResponse.get_body();
    
    ofstream f;
    f.open("test.mp3", ios::binary);
    for(auto v : body)
        f << v;
    f.close();
    return 0;
}
```
