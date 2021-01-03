#ifndef _STUDENT_H_INCLUDED
#define _STUDENT_H_INCLUDED
#include "Account.h"
#include "Admin.h"
#include <vector>
class student : public account
{
public:
    student(int n, string password) : account(n, password) {}
    student() {}
    void homepage() //管理员账户的主界面
    {
        std::cout << "现在登录的是管理员账户，请输入您要执行的操作对应的序号。\n1-添加图书 | 2-修改图书 | 3-搜索图书 | 4-删除图书 | 5-添加学生账号 | 6-修改账号 | 7-退出到主页面 | 其他-退出登录\n请注意，管理员账号只能在开始时导入。\n";
        int operation;
        cin >> operation;
        switch (operation)
        {
        case 1:
            library.add();
            break;
        case 2:
            std::cout << "请输入您想修改图书的编号\n";
            int num;
            cin >> num;
            library.modify(num);
            break;
        case 3:
        {
            account::searchBook(library);
        }
        case 4:
            std::cout << "请输入您想删除图书的编号\n";
            cin >> num;
            library.deleteBook(num);
            break;
        case 5: //添加学生账号
            studentList.push_back(student());
            break;
        case 6:
            std::cout << "请输入您想修改的账号位置以及其位置以及其编号或学号\n";
            cin >> num; //修改的账户位置
            account::modify();
            break;
        case 7:
        {
            homepage();
            break;
        }
        default:
            break;
        }
        return;
    }
    friend class admin;
};
vector<student> studentList;
#endif