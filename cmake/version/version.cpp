#include "lib.h"
#include <iostream>
#include "versionProjConfig.h" // cmake 自动生成的头文件

using namespace std;

int main()
{
    printf("%d\n", v1);
    printf("%d\n", v2);

    string str("hello world");
    cout << ReverseString(str) << endl;

    return 0;
}