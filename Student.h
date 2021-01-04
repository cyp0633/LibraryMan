#ifndef _STUDENT_H_INCLUDED
#define _STUDENT_H_INCLUDED
#include "Account.h"
#include "variable.h"
class account;
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;
extern vector<student> studentList;
extern vector<admin> adminList;
extern repo library;
class student : public account
{
private:
    int a;

public:
    student() {}
    student(int id, string pswd)
    {
        account(id,pswd);
    }
    void homepage();
};
//vector<student> studentList;
#endif