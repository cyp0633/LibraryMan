#ifndef _ERROR_INCLUDED_
#define _ERROR_INCLUDED_
#include<iostream>
using namespace std;
template<class x>
extern x getInt (x t)
{
    x temp;
    back:
    cin>>temp;
    cin.ignore(1024,'\n');
    if(cin.fail())
    {
        cout<<"请输入整型数字"<<endl;
        cin.clear();
        cin.sync();
        goto back;
    }
    return temp;
}
#endif