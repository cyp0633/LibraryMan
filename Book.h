#ifndef _BOOK_H_INCLUDED
#define _BOOK_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;
class Book
{
private:
    bool borrowed; //是否被借走了

public:
    string title;    //题名
    bool serial;     //是否为连续出版物(ISSN)
    string num;      //ISBN/ISSN
    string author;   //作者
    string category; //三级分类
    bool deleted;    //是否被删除
    Book(int n);
    Book()
    {
        borrowed = false;
        deleted = false;
        return;
    }
    void printInfo() { return; }
    void setBook_manual();
    bool returnBook(); //还书
    bool borrow();
    bool operator<(const Book &another) const //重载小于运算符，实现基于标题的比较大小
    {
        return this->title < another.title;
    }
    friend ostream &operator<<(ostream &output, Book b);
};
ostream &operator<<(ostream &output, Book b) //输出书本信息
{
    if (b.deleted)
    {
        std::cout << "本书不存在！";
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
    return output;
}
Book::Book(int n)
{
    std::cout << "请输入要添加的信息。";
    std::cout << "题目: ";
    cin >> title;
    std::cout << "ISBN/ISSN: ";
    cin >> num;
    if (num.length() >= 11) //ISBN有11位，ISSN只有8位。判断是否为连续出版物，适用ISBN还是ISSN
    {
        serial = false; //
    }
    else
    {
        serial = true;
    }
    std::cout << "作者: ";
    cin >> author;
    std::cout << "三级分类(如A751/6 1): ";
    getline(cin, category);
    borrowed = false;
    deleted = false;
    return;
}
void Book::setBook_manual()
{
    if (deleted)
    {
        std::cout << "本书不存在！";
        return;
    }
    std::cout << "下面是本书的基本信息。\n";
    std::cout << *this;
    std::cout << "请输入您想修改的信息对应的序号：\n1-题目 | 2-ISBN/ISSN | 3-作者 | 4-分类\n";
    int infoNum;
    cin >> infoNum;
    switch (infoNum)
    {
    case 1:
        std::cout << "请输入新题目:";
        cin >> title;
        break;
    case 2:
        std::cout << "请输入新ISBN/ISSN:";
        cin >> num;
        break;
    case 3:
        std::cout << "请输入新作者信息:";
        cin >> author;
        break;
    case 4:
        std::cout << "请输入新分类:";
        cin >> category;
        break;
    }
    return;
}
bool Book::borrow() //借书
{
    if (deleted)
    {
        std::cout << "本书不存在！";
        return false;
    }
    if (borrowed)
    {
        std::cout << "抱歉，此书已被借走。\n";
        return false;
    }
    borrowed = true;
    std::cout << "成功借书！\n";
    return true;
}
bool Book::returnBook() //还书
{
    if (deleted)
    {
        std::cout << "本书不存在！";
        return false;
    }
    if (!borrowed)
    {
        std::cout << "这本书并没有被借走，你是想再送给我们一本嘛？\n";
        return false;
    }
    borrowed = false;
    std::cout << "成功还书！\n";
    return true;
}
#endif