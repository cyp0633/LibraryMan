#ifndef _BOOK_H_INCLUDED
#define _BOOK_H_INCLUDED
#include <iostream>
#include <string>
#include "error.h"
using namespace std;
class Book
{
private:
    //bool borrowed; //是否被借走了

public:
    string title;    //题名
    bool serial;     //是否为连续出版物(ISSN)
    string num;      //ISBN/ISSN
    string author;   //作者
    string category; //三级分类
    int remainingNum;
    bool deleted; //是否被删除
    Book()        //自动导入用这个构造
    {
        deleted = false;
    }
    Book(int n) //手动添加用这个构造
    {
        deleted = false;
        cout << "请输入书名:\n";
        cin >> title;
        cout << "请输入作者:\n";
        cin >> author;
        cout << "请输入ISBN/ISSN:\n";
        cin >> num;
        cout << "请输入分类:";
        cin >> category;
        cout << "请输入库存数量:\n";
        cin >> remainingNum;
        return;
    }
    void printInfo()
    {
        return;
    }
    void setBook_manual()
    {
        if (deleted)
        {
            cout << "本书不存在！";
            return;
        }
        cout << "下面是本书的基本信息。\n";
        cout << *this;
        cout << "请输入您想修改的信息对应的序号：\n1-题目 | 2-ISBN/ISSN | 3-作者 | 4-分类 | 5-剩余数量\n";
        int infoNum;
        infoNum = getInt(infoNum);
        switch (infoNum)
        {
        case 1:
            cout << "请输入新题目:\n";
            cin >> title;
            break;
        case 2:
            cout << "请输入新ISBN/ISSN:\n";
            cin >> num;
            break;
        case 3:
            cout << "请输入新作者信息:\n";
            cin >> author;
            break;
        case 4:
            cout << "请输入新分类:\n";
            cin >> category;
            break;
        case 5:
            cout << "请输入新数量:\n";
        }
        return;
    }
    bool borrow() //借书
    {
        if (!remainingNum)
        {
            cout << "抱歉，此书已被借完或者被删除。\n";
            return false;
        }
        remainingNum++;
        cout << "成功借书！\n";
        return true;
    }
    bool returnBook() //还书
    {
        remainingNum++;
        cout << "成功还书！\n";
        return true;
    }
    bool operator<(const Book &another) const //重载小于运算符，实现基于标题的比较大小
    {
        return this->title < another.title;
    }
    friend ostream &operator<<(ostream &output, Book b);
    void modify();
};
ostream &operator<<(ostream &output, Book b) //输出书本信息
{
    if (b.deleted)
    {
        output << "本书不存在！\n";
        return output;
    }
    output << "题目:" << b.title << '\n';
    output << "作者:" << b.author << '\n';
    if (b.serial)
    {
        output << "ISSN:" << b.num << '\n';
    }
    else
    {
        output << "ISBN:" << b.num << '\n';
    }
    output << "分类:" << b.category << '\n';
    output << "剩余本数:" << b.remainingNum << '\n';
    return output;
}
#endif