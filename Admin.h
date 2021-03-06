#ifndef _ADMIN_H_INCLUDED_
#define _ADMIN_H_INCLUDED_
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "Repo.h"
#include "Student.h"
#include "Error.h"
class repo;
class student;
using namespace std;
void accountSwitcher(vector<student> &studentList, vector<admin> &adminList, repo &library);
void accountSwitcherNew(vector<student> &studentList, vector<admin> &adminList, repo &library);
pair<bool, int> accountFinder(vector<student> &studentList, vector<admin> &adminList, long long int id);
class admin
{
private:
    long long int username; //用户名
    string password;        //密码
    list<int> borrowedBook; //借了的书，使用链表存储，好删除
public:
    void homepage(vector<student> &studentList, vector<admin> &adminList, repo &library); //管理员账户的主界面
    admin()
    {
        cout << "请输入学工号数字:\n";
        username = getInt(username);
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
    admin(const long long int &id, const string &pswd)
    {
        username = id;
        password = pswd;
    }
    void deleteBook(repo &library);
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
            target = getInt(target);
            bookNum = library.searchTitle(target, 1);

            break;
        case 3:
            cout << "请输入您想查找的作者:";
            target = getInt(target);
            bookNum = library.searchAuthor(target, 1);
            break;
        case 2:
            cout << "请输入您想查找的ISBN/ISSN，记得输入中间的连字符:";
            target = getInt(target);
            bookNum = library.searchISBN(target, 1);
            break;
        case 4:
            cout << "请输入您感兴趣的分类:";
            target = getInt(target);
            bookNum = library.searchCategory(target, 1);
        }
        if (bookNum == -1) //找不到这本书
        {
            return;
        }
        if (library.bookList[bookNum].borrow()) //书被成功借走，会返回true，这样才会计入借走的列表
        {
            borrowedBook.push_back(bookNum);
            library.addBorRec(time(NULL), username, bookNum, 1);
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
void admin::homepage(vector<student> &studentList, vector<admin> &adminList, repo &library)
{
    cout << "您现在处于管理员账户。请输入您的操作类别。\n1-书库操作 | 2-图书操作 | 3-账户操作 | 4-记录查询 | 5-退出账号\n";
    int opt1, opt2;
    opt1 = getInt(opt1);
    switch (opt1)
    {
    case 1: //书库操作
    {
        cout << "请选择操作。\n1-手动添加图书 | 2-修改图书 | 3-从文件导入图书 | 4-删除图书 | 其他-返回上一级\n";
        opt2 = getInt(opt2);
        switch (opt2)
        {
        case 1:
            library.add();
            break;
        case 2:
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
            library.fileImport();
            break;
        case 4:
            deleteBook(library);
            break;
        }
        break;
    }
    case 2: //图书操作
    {
        cout << "请选择操作。\n1-搜索图书 | 2-借阅图书 | 3-归还图书 | 其他-返回上一级\n";
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
    }
    case 3: //账户操作
    {
        cout << "请选择操作。\n1-增加学生账号 | 2-修改账号 | 其他-返回上一级\n";
        opt2 = getInt(opt2);
        switch (opt2)
        {
        case 1:
            studentList.push_back(student());
            break;
        case 2: //待做
            cout << "请输入待修改的人学号\n";
            long long int id;
            pair<bool, int> target = accountFinder(studentList, adminList, id);
            if (target.first && target.second == -1)
            {
                cout << "未找到该账号。\n";
                break;
            }
            if (target.first)
            {
                studentList[target.second].modify();
            }
            else
            {
                adminList[target.second].modify();
            }
            cout << "已修改。\n";
            break;
        }
        break;
    }
    case 4:
    {
        cout << "请选择操作。\n1-查阅入馆记录 | 2-查阅全馆借阅记录 | 3-查阅自身借阅记录 | 其他-返回上一级\n";
        opt2 = getInt(opt2);
        if (opt2 > 3 || opt2 < 1)
        {
            break;
        }
        int startTime, endTime;
        cout << "请输入要查询的起止时间(时间戳格式)，值均为0代表查询全部。";
        startTime = getInt(startTime);
        endTime = getInt(endTime);
        switch (opt2)
        {
        case 1:
            library.displayLogRec(startTime, endTime);
            break;
        case 2:
            library.displayBorRec(startTime, endTime);
            break;
        case 3:
            printBorrowedBooks(library);
            break;
        }
        break;
    }
    case 5:
        accountSwitcherNew(studentList, adminList, library);
        return;
    }
    homepage(studentList, adminList, library);
}
void admin::deleteBook(repo &library) //删除图书
{
    cout << "您想删除哪本书？请输入书名，支持模糊搜索。\n";
    string title;
    cin >> title;
    int deleteNum = library.searchTitle(title, 1);
    library.deleteBook(deleteNum);
}
void admin::modify()
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
void admin::printBorrowedBooks(repo &library)
{
    cout << "已借阅书籍如下，共" << borrowedBook.size() << "本:\n";
    for (list<int>::iterator i = borrowedBook.begin(); i != borrowedBook.end(); i++)
    {
        cout << "《" << library.bookList[*i].title << "》\n";
    }
}
void admin::returnBook(repo &library)
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