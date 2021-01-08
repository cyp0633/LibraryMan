#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Admin.h"
#include "Book.h"
#include "KMP.h"
#include "Repo.h"
#include "Student.h"
#include "Account.h"
#include "error.h"
using namespace std;
class student;
class admin;
int main()
{
    //system("cls");
    vector<student> studentList;
    vector<admin> adminList;
    repo library;
    cout << "您想要导入账号数据，还是创建一个新设置？\n1-从文件导入账号数据 | 2-创建新账号数据\n";
    std::cout << "需要创建第一个管理员账户才可继续。\n";
    int newAccountMethod = getInt(newAccountMethod);
    if (newAccountMethod == 1)
    {
        fileImportAccount(studentList, adminList);
    }
    else
    {
        adminList.push_back(admin());
    }
    cout << "正在跳转登录界面。\n";
    accountSwitcherNew(studentList, adminList, library);
    return 0;
}
