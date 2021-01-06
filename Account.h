#ifndef _ACCOUNT_H_INCLUDED
#define _ACCOUNT_H_INCLUDED
#include <iostream>
#include <regex>
#include <string>
#include <list>
#include <fstream>
#include "Repo.h"
#include "Student.h"
#include "Admin.h"
using namespace std;
class student;
class admin;
void fileImportAccount(vector<student> &studentList, vector<admin> &adminList)
{
    cout << "即将从account.txt读取账户信息,请确认没有重复的账号。\n请注意：密码格式为字母开头，可以包含字母/数字/下划线，6-17位。\n如果不符合要求，将不会导入。\n";
    string username;
    string password;
    int count = 0;
    regex passFormat("^[a-zA-Z][a-zA-Z0-9_]{5,17}$");
    ifstream accountImport;
    accountImport.open("account.txt", ios::in);
    accountImport >> username >> password;
    while (accountImport >> username >> password)
    {
        if (username == "STUDENT")
        {
            break;
        }
        adminList.push_back(admin(stoi(username), password));
        count++;
    }
    while (accountImport >> username >> password)
    {
        studentList.push_back(student(stoi(username), password));
        count++;
    }
    accountImport.close();
    cout << "导入完成，共导入" << count << "个账号。\n";
    return;
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
pair<bool, int> accountFinder(vector<student> &studentList, vector<admin> &adminList, long long int id) //账号查找
{
    for (vector<student>::iterator i = studentList.begin(); i != studentList.end(); i++)
    {
        if (id == i->username)
        {
            return pair<bool, int>(0, &*i - &studentList[0]); //返回账号下标
        }
    }
    for (vector<admin>::iterator i = adminList.begin(); i != adminList.end(); i++)
    {
        if (id == i->username)
        {
            return pair<bool, int>(1, &*i - &adminList[0]);
        }
    }
    return pair<bool, int>(1, -1);
}
#endif