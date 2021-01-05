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
    accountImport>>username>>password;
    while (accountImport >> username >> password)
    {
        if (username == "STUDENT")
        {
            break;
        }
        studentList.push_back(student(stoi(username), password));
        count++;
    }
    while (accountImport >> username >> password)
    {
        adminList.push_back(admin(stoi(username), password));
        count++;
    }
    accountImport.close();
    cout << "导入完成，共导入" << count << "个账号。\n";
    return;
}

#endif