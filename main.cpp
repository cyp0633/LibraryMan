#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int bookCount;
class Book
{
private:
    bool borrowed; //是否被借走了
public:
    Book()
    {
        string title;            //题名
        bool serial;             //是否为连续出版物(ISSN)
        string num;              //ISBN/ISSN
        string author;           //作者
        string cat1, cat2, cat3; //三级分类
        bookCount++;
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
        return true;
    }
    bool returnBook() //还书
    {
        if (!borrowed)
        {
            cout << "这本书并没有被借走";
            return false;
        }
        borrowed = false;
        return true;
    }
};
int main()
{
    return 0;
}