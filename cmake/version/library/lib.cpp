#include "lib.h"

string ReverseString(const string& str)
{
    string ret_str = str;
    reverse(ret_str.begin(), ret_str.end());
    return ret_str;
}