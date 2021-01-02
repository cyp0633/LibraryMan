#ifndef _ACCOUNT_H_INCLUDED
#define _ACCOUNT_H_INCLUDED
#include <iostream>
#include <regex>
#include "Repo.h"
#include "Book.h"
#include "Admi.h"
#include "Student.h"
#include <string>
#include <list>
#include <fstream>
using namespace std;
class account
{
private:
    int username;           //用户名
    string password;        //密码
    list<int> borrowedBook; //借了的书，使用链表存储，好删除  借书记录
public:
    account()
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
    account(int n, string pswd) : username(n), password(pswd) {}
    void modify()
    {
        cout << "请输入新学号:";
        cin >> username;
        cout << "请输入新密码:";
        cin >> password;
        regex passFormat("^[a-zA-Z][a-zA-Z0-9_]{5,17}$");
        while (regex_match(password, passFormat))
        {
            cout << "密码格式不正确。请再输入一次。\n";
            cin >> password;
        }
    }
    void borrowBook(repo &r) //借书功能
    {
        cout << "您想怎样找到您想要的书？\n1.题名 | 2.ISBN/ISSN | 3.作者 | 4.分类号\n对于分类号，您可以使用任一级分类查找；作者无法模糊查找，必须匹配名字；题名和ISBN/ISSN可以模糊匹配，您只需要输入一部分。\n请输入您想查找的类型前的数字：";
        int type, bookNum;
        string target;
        cin >> type;
        switch (type)
        {
        case 1:
            cout << "请输入您想查找的题名:";
            cin >> target;
            bookNum = r.searchTitle(target, 1);

            break;
        case 3:
            cout << "请输入您想查找的作者:";
            cin >> target;
            bookNum = r.searchAuthor(target, 1);
            break;
        case 2:
            cout << "请输入您想查找的ISBN/ISSN，记得输入中间的连字符:";
            cin >> target;
            bookNum = r.searchISBN(target, 1);
            break;
        case 4:
            cout << "请输入您感兴趣的分类:";
            cin >> target;
            bookNum = r.searchCategory(target, 1);
        }
        if (r.bookList[bookNum].borrow()) //书被成功借走，会返回true，这样才会计入借走的列表
        {
            borrowedBook.push_back(bookNum);
            cout << "您借走的书馆内编号为" << bookNum << "，请妥善保管此数字，还书时将用到。";
            r.borRec.push_back(borrowRecord(time(NULL), username, bookNum));
        }
        return;
    }
    void searchBook(repo &r) //找书功能
    {
        cout << "您想怎样找到您想要的书？\n1.题名 | 2.ISBN/ISSN | 3.作者 | 4.分类号\n对于分类号，您可以使用任一级分类查找；作者无法模糊查找，必须匹配名字；题名和ISBN/ISSN可以模糊匹配，您只需要输入一部分。\n请输入您想查找的类型前的数字：";
        int type;
        string target;
        cin >> type;
        switch (type)
        {
        case 1:
            cout << "请输入您想查找的题名:";
            cin >> target;
            r.searchTitle(target, 0);
            break;
        case 3:
            cout << "请输入您想查找的作者:";
            cin >> target;
            r.searchAuthor(target, 0);
            break;
        case 2:
            cout << "请输入您想查找的ISBN/ISSN，记得输入中间的连字符:";
            cin >> target;
            r.searchISBN(target, 0);
            break;
        case 4:
            cout << "请输入您感兴趣的分类:";
            cin >> target;
            r.searchCategory(target, 0);
        }
    }
    void returnBook(repo &r)
    {
        int bookNum;
        cout << "请输入想还的书的馆内编号:";
        cin >> bookNum;
        list<int>::iterator i;
        for (i = borrowedBook.begin(); i != borrowedBook.end(); i++)
        {
            if (*i == bookNum) //找到了要还的书
            {
                if (r.bookList[bookNum].returnBook())
                {
                    borrowedBook.erase(i);
                    cout << "成功还书!\n";
                }
                else
                {
                    cout << "还书不成功。\n";
                }

                break;
            }
        }
    }
};
void fileImportAccount()
{
    cout << "即将从account.txt读取账户信息,请确认没有重复的账号。\n请注意：密码格式为字母开头，可以包含字母/数字/下划线，6-17位。\n如果不符合要求，将不会导入。";
    string username;
    string password;
    int count = 0;
    regex passFormat("^[a-zA-Z][a-zA-Z0-9_]{5,17}$");
    ifstream accountImport;
    accountImport.open("account.txt", ios::in);
    getline(accountImport, username);
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