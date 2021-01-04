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
    void homepage(); //管理员账户的主界面

    void deleteBook();
};
vector<admin> adminList;
void admin::homepage()
{
    cout << "现在登录的是管理员账户，请输入您要执行的操作对应的序号。\n1-添加图书 | 2-修改图书 | 3-搜索图书 | 4-删除图书 | 5-借阅图书\n6-归还图书 | 7-添加学生账号 | 8-修改账号 | 9-退出到主页面 | 其他-退出账号\n";
    int operation;
    cin >> operation;
    switch (operation)
    {
    case 1: //添加图书
        library.add();
        break;
    case 2: //修改图书
    {
        cout << "您想修改哪本书？支持题目模糊搜索。\n";
        string title;
        cin >> title;
        int num;
        num = library.searchTitle(title, 1);
        library.bookList[num].setBook_manual();
        break;
    }
    case 3:
        searchBook(library);
        break;
    case 4:
        deleteBook();
        break;
    case 5:
        borrowBook(library);
        break;
    case 6:
        returnBook(library);
        break;
    case 7:
        studentList.push_back(student());
        break;
    case 9:
        homepage();
        break;
    default:
        return;
    }
}
void admin::deleteBook() //删除图书
{
    cout << "您想输出哪本书？请输入书名，支持模糊搜索。\n" string title;
    cin >> title;
    int deleteNum = library.searchTitle(title, 1);
    library.deleteBook(deleteNum);
}
#endif