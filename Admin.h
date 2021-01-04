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
    void homepage() //管理员账户的主界面
    {
        cout << "现在登录的是管理员账户，请输入您要执行的操作对应的序号。\n1-添加图书 | 2-修改图书 | 3-搜索图书 | 4-删除图书 | 5-借阅图书 | 6-添加学生账号 | 7-修改账号 | 8-退出到主页面 | 其他-退出账号\n";
        int operation;
        cin >> operation;
        switch (operation)
        {
        case 1://添加图书
            library.add();
            break;
        case 2://修改图书
        {
            cout<<"您想修改哪本书？支持题目模糊搜索。\n";
            string title;
            cin>>title;
            int num;
            num=library.searchTitle(title,1);
            library.bookList[num].setBook_manual();
            break;
        }
        case 3:
            
        case 7:
            homepage();
            break;
        default:
            return;
        }
    }
};
vector<admin> adminList;
#endif