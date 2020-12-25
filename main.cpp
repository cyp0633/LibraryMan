#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
class Book
{
private:
    bool borrowed; //是否被借走了
public:
    void setBook(const int bookCount)
    {
        string title;            //题名
        bool serial;             //是否为连续出版物(ISSN)
        string num;              //ISBN/ISSN
        string author;           //作者
        string cat1, cat2, cat3; //三级分类
        cout << "您正在录入第" << bookCount << "本图书的信息。\n";
        cout << "题目: ";
        cin >> title;
        cout << "ISBN/ISSN: ";
        cin >> num;
        if (num.length() >= 11) //ISBN有11位，ISSN只有8位。判断是否为连续出版物，适用ISBN还是ISSN
        {
            serial = false;
        }
        else
        {
            serial = true;
        }
        cout << "作者: ";
        cin >> author;
        cout << "三级分类(由空格分隔，1级 2级 3级): ";
        cin >> cat1 >> cat2 >> cat3;
        borrowed = false;
        return;
    }
    bool borrow() //借书
    {
        if (borrowed)
        {
            cout << "抱歉，此书已被借走。";
            return false;
        }
        borrowed = true;
        cout << "成功借书！";
        return true;
    }
    bool returnBook() //还书
    {
        if (!borrowed)
        {
            cout << "这本书并没有被借走，你是想再送给我们一本嘛？";
            return false;
        }
        borrowed = false;
        cout << "成功还书！";
        return true;
    }
};
class repo //书库
{
private:
    Book bookList[10000]; //暂时使用数组实现，试试啥时候能用链表
    int bookCount = 0;

public:
    repo() {}
    void addBook() //增加图书功能
    {
        bookList[bookCount].setBook(bookCount);
        bookCount++;
    }
    void modBook(int num) //修改图书功能
    {
        bookList[bookCount].setBook(bookCount);
    }
};
class account
{
};
class student : public account
{
};
class admin : public account
{
};
int main()
{
    return 0;
}