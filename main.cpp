#include <cstdio>
#include <iostream>
#include <vector>
#include "Account.h"
#include "Admin.h"
#include "Book.h"
#include "KMP.h"
#include "Repo.h"
#include "Student.h"
using namespace std;
vector<student> studentList;
vector<admin> adminList;
repo library;
int main()
{
    cout << "您想要导入账号数据，还是创建一个新设置？\n1-从文件导入账号数据 | 2-创建新账号数据\n";
    int newAccountMethod;
    cout << "需要创建第一个管理员账户才可继续。\n";
    cin>>newAccountMethod;
    if(newAccountMethod==1)
    {
        fileImportAccount();
    }
    else
    {
        adminList.push_back(admin());
        cout << "现在将登入这个账号……";
    }
    return 0;
}
