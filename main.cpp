#include <cstdio>
#include <iostream>
#include <vector>
#include "Admin.h"
#include "Book.h"
#include "KMP.h"
#include "Repo.h"
#include "Student.h"
#include "Account.h"
using namespace std;
class student;
class admin;
void accountSwitcher(vector<student> &studentList, vector<admin> &adminList, repo &library);
int main()
{
    vector<student> studentList;
    vector<admin> adminList;
    repo library;
    cout << "您想要导入账号数据，还是创建一个新设置？\n1-从文件导入账号数据 | 2-创建新账号数据\n";
    int newAccountMethod;
    cout << "需要创建第一个管理员账户才可继续。\n";
    cin>>newAccountMethod;
    if(newAccountMethod==1)
    {
        fileImportAccount(studentList,adminList);
    }
    else
    {
        adminList.push_back(admin());
    }
    cout<<"正在跳转登录界面。\n";
    accountSwitcher(studentList,adminList,library);
    return 0;
}
void accountSwitcher(vector<student> &studentList, vector<admin> &adminList, repo &library)
{
    cout << "欢迎登录，请输入您的账号。\n";
    long long int id;
    string pswd;
    cin >> id;
    cout << "请输入密码。\n";
    cin >> pswd;
    for (vector<student>::iterator i = studentList.begin(); i != studentList.end(); i++)
    {
        int statusValue = i->verify(id, pswd);
        switch (statusValue)
        {
        case 1:
            cout << "登陆成功！您的账号是学生账号。\n";
            i->homepage(studentList, adminList, library);
            return;
        case -1:
            cout << "密码错误！\n";
            break;
        default:
            break;
        }
    }
    for (vector<admin>::iterator i = adminList.begin(); i != adminList.end(); i++)
    {
        int statusValue = i->verify(id, pswd);
        switch (statusValue)
        {
        case 1:
            cout << "登陆成功！您的账号是管理员账号。\n";
            i->homepage(studentList, adminList, library);
            return;
        case -1:
            cout << "密码错误！\n";
            break;
        default:
            break;
        }
    }
    cout << "登录失败，可能是密码错误或者没有找到账号。\n";
    accountSwitcher(studentList, adminList, library);
    return;
}