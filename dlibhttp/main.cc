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
