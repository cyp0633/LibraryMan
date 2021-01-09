#ifndef _STUDENT_H_INCLUDED
#define _STUDENT_H_INCLUDED
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <regex>
#include <list>
#include "Admin.h"
using namespace std;
class admin;
class student
{
private:
    long long int username; //用户名
    string password;        //密码
    list<int> borrowedBook; //借了的书，使用链表存储，好删除
public:
    student()
    {
        cout << "请输入学工号数字:\n";
        cin >> username;
        cout << "请输入密码。\n要求：字母开头，可以包含字母/数字/下划线，6-17位：\n";
        cin >> password;
        regex passFormat("^[a-zA-Z][a-zA-Z0-9_]{5,17}$");
        while (!regex_match(password, passFormat))
        {
            cout << "密码格式不正确。请再输入一次。\n";
            cin >> password;
        }
        cout << "成功创建账号。\n";
    }
    student(const long long int id, const string pswd)
    {
        username = id;
        password = pswd;
    }
    void homepage(vector<student> &studentList, vector<admin> &adminList, repo &library);
    int verify(long long int id, string pswd)
    {
        if (id == username)
        {
            if (pswd == password)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return 0;
        }
    }
    void borrowBook(repo &library) //借书功能
    {
        cout << "您想怎样找到您想要的书？\n1.题名 | 2.ISBN/ISSN | 3.作者 | 4.分类号\n对于分类号，您可以使用任一级分类查找；作者无法模糊查找，必须匹配名字；题名和ISBN/ISSN可以模糊匹配，您只需要输入一部分。\n请输入您想查找的类型前的数字：";
        int type, bookNum;
        string target;
        type = getInt(type);
        switch (type)
        {
        case 1:
            cout << "请输入您想查找的题名:";
            cin >> target;
            bookNum = library.searchTitle(target, 1);

            break;
        case 3:
            cout << "请输入您想查找的作者:";
            cin >> target;
            bookNum = library.searchAuthor(target, 1);
            break;
        case 2:
            cout << "请输入您想查找的ISBN/ISSN，记得输入中间的连字符:";
            cin >> target;
            bookNum = library.searchISBN(target, 1);
            break;
        case 4:
            cout << "请输入您感兴趣的分类:";
            cin >> target;
            bookNum = library.searchCategory(target, 1);
        }
        if (bookNum == -1) //找不到这本书
        {
            return;
        }
        if (library.bookList[bookNum].borrow()) //书被成功借走，会返回true，这样才会计入借走的列表
        {
            borrowedBook.push_back(bookNum);
            library.addBorRec(time(NULL), username, bookNum, 0);
        }
        return;
    }
    void searchBook(repo &library) //找书功能
    {
        cout << "您想怎样找到您想要的书？\n1.题名 | 2.ISBN/ISSN | 3.作者 | 4.分类号\n对于分类号，您可以使用任一级分类查找；作者无法模糊查找，必须匹配名字；题名和ISBN/ISSN可以模糊匹配，您只需要输入一部分。\n请输入您想查找的类型前的数字：";
        int type;
        string target;
        type = getInt(type);
        switch (type)
        {
        case 1:
            cout << "请输入您想查找的题名:";
            cin >> target;
            library.searchTitle(target, 0);
            break;
        case 3:
            cout << "请输入您想查找的作者:";
            cin >> target;
            library.searchAuthor(target, 0);
            break;
        case 2:
            cout << "请输入您想查找的ISBN/ISSN，记得输入中间的连字符:";
            cin >> target;
            library.searchISBN(target, 0);
            break;
        case 4:
            cout << "请输入您感兴趣的分类:";
            cin >> target;
            library.searchCategory(target, 0);
        }
    }
    void returnBook(repo &library);
    friend pair<bool, int> accountFinder(vector<student> &studentList, vector<admin> &adminList, long long int id);
    void modify();
    void printBorrowedBooks(repo &library);
    friend void fileImportAccount(vector<student> &studentList, vector<admin> &adminList);
};
void student::modify()
{
    cout << "该账号学号为" << username << ",密码为" << password << "。您想修改什么？\n1-学号 | 2-密码\n";
    int opt;
    opt = getInt(opt);
    switch (opt)
    {
    case 1:
        cout << "请输入新学号\n";
        cin >> username;
        break;
    case 2:
        cout << "请输入新密码\n";
        cin >> password;
        break;
    }
    cout << "修改完成\n";
    return;
}
void accountSwitcher(vector<student> &studentList, vector<admin> &adminList, repo &library);
void accountSwitcherNew(vector<student> &studentList, vector<admin> &adminList, repo &library);
void student::homepage(vector<student> &studentList, vector<admin> &adminList, repo &library)
{
    int opt1, opt2;
    cout << "您现在处于学生账户，请输入您的操作类别。\n1-图书操作 | 2-修改账号信息 | 3-查询本人借阅记录 | 4-退出账号\n";
    opt1 = getInt(opt1);
    switch (opt1)
    {
    case 1:
        cout << "请输入操作序号。\n1-搜索图书 | 2-借阅图书 | 3-归还图书 | 其他-回到上一级\n";
        opt2 = getInt(opt2);
        switch (opt2)
        {
        case 1:
            searchBook(library);
            break;
        case 2:
            borrowBook(library);
            break;
        case 3:
            returnBook(library);
            break;
        }
        break;
    case 2:
        modify();
        break;
    case 3:
        printBorrowedBooks(library);
        break;
    case 4:
        accountSwitcherNew(studentList, adminList, library);
        return;
    }
    homepage(studentList, adminList, library);
    return;
}
void student::printBorrowedBooks(repo &library)
{
    cout << "已借阅书籍如下，共" << borrowedBook.size() << "本:\n";
    for (list<int>::iterator i = borrowedBook.begin(); i != borrowedBook.end(); i++)
    {
        cout << "《" << library.bookList[*i].title << "》\n";
    }
}
void student::returnBook(repo &library)
{
    cout << "这是您目前已借的书目录。\n";
    int target, borrowCount = 0;
    list<int>::iterator i;
    for (i = borrowedBook.begin(); i != borrowedBook.end(); i++)
    {
        borrowCount++;
        cout << setw(4) << left << borrowCount << " - \"" << library.bookList[*i].title << "\"\n";
    }
    cout << "请选择要还的书。";
    cin >> target;
    // i=borrowedBook.begin()+target-1;
    i = borrowedBook.begin();
    for (int x = 0; x < target - 1; x++)
    {
        i++;
    }
    library.bookList[*i].returnBook();
    borrowedBook.erase(i);
    return;
}
#endif