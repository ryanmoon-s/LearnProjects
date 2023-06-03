#include "lib.h"
#include <iostream>
#include "versionProjConfig.h" // cmake 自动生成的头文件

using namespace std;

int main()
{
    #ifdef MY_DEF_1
    printf("%d\n", v1);
    #endif

    printf("%d, %d\n", v2, MY_DEF_2);

    string str("hello world");
    cout << ReverseString(str) << endl;

    return 0;
}