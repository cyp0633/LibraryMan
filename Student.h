#ifndef _STUDENT_H_INCLUDED
#define _STUDENT_H_INCLUDED
#include "Account.h"
#include <vector>
class student : public account
{
    public:
    student(int n,string password):account(n,password){}
    
};
vector<student> studentList;
#endif