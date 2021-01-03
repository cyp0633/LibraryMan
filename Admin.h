#ifndef _ADMIN_H_INCLUDED_
#define _ADMIN_H_INCLUDED_
#include "Account.h"
#include "Student.h"
#include <iostream>
#include <vector>
using namespace std;

class admin : public account
{
public:
    admin(int n, string password) : account(n, password) {}
    admin() {}
    void homepage(); //管理员账户的主界面
};
vector<admin> adminList;
#endif
void admin::homepage()
{
    {
        std::cout << "现在登录的是管理员账户，请输入您要执行的操作对应的序号。\n1-添加图书 | 2-修改图书 | 3-搜索图书 | 4-删除图书 | 5-添加学生账号 | 6-修改账号 | 7-退出到主页面,输入其他数字退出登录";
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
            searchBook(library);
        }
        case 4:
            std::cout << "请输入您想删除图书的编号\n";
            cin >> num;
            library.deleteBook(num);
            break;
        case 5: //添加账号
            studentList.push_back(student());
            break;
        case 6: //修改账号
        {
            int id;
            char type;
            cout << "请选择您想更改的账户类型。\nA-管理员 | B-学生\n";
            cin >> type;
            cout << "请选择您想更改的ID";
            cin >> id;
            if (type == 'A')
            {
                vector<admin>::iterator i;
                for (i = adminList.begin(); i != adminList.end(); i++)
                {
                    if (i->username == id)
                    {
                        i->modifyData();
                        break;
                    }
                }
            }
        }
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
}