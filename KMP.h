#ifndef _KMP_H_INCLUDED_
#define _KMP_H_INCLUDED_
#include <string>
#include <iostream>
using namespace std;
bool kmp(string a, string b) //KMP是一种字符串匹配算法，可以实现b部分匹配a的查找。
{
    int lena = a.length(), lenb = b.length(), startPos = 0, searchPos = 0;
    if (lena > lenb)
    {
        cerr << "错误:请输入搜索对象的全部或一部分。\n";
        return false;
    }
    if (a == b)
    {
        return true;
    }
    for (startPos = 0; startPos <= lenb - lena; startPos++)
    {
        for (searchPos = 0; searchPos < lena; searchPos++)
        {
            if (a[searchPos] != b[startPos + searchPos])
            {
                startPos += searchPos;
                break;
            }
        }
        if (searchPos == lena)
        {
            return true;
        }
    }
    return false;
}
#endif