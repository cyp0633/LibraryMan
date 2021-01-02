#ifndef _ADMI_H_INCLUDED_
#define _ADMI_H_INCLUDED_
#include "Account.h"
#include <iostream>
#include <vector>
using namespace std;
class admin : public account
{
public:
    void homepage() //管理员账户的主界面
    {
        cout << "现在登录的是管理员账户，请输入您要执行的操作对应的序号。\n1-添加图书 | 2-修改图书 | 3-搜索图书 | 4-添加账号 | 5-修改账号 | 6-退出到主页面";
        int operation;
        cin >> operation;
        switch (operation)
        {
        case 1:
            library.add();
            break;
        case 2:
            break;
        }
        homepage();
        return;
    }
};
vector<admin> adminList;
#endif