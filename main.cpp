#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
bool kmp(string a, string b);
class Book
{
private:
    bool borrowed; //是否被借走了
public:
    string title;            //题名
    bool serial;             //是否为连续出版物(ISSN)
    string num;              //ISBN/ISSN
    string author;           //作者
    string cat1, cat2, cat3; //三级分类
    void setBook(const int bookCount)
    {
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
    bool operator<(Book &another) //重载小于运算符，实现基于标题的比较大小
    {
        return this->title < another.title;
    }
};
class repo //书库
{
private:
    Book *bookList; //暂时使用数组实现，试试啥时候能用链表
    int bookCount = 0;

public:
    repo()
    {
        bookList = new Book[100000];
    }
    void add() //增加图书功能
    {
        bookList[bookCount].setBook(bookCount);
        bookCount++;
    }
    void modify(int num) //修改图书功能，num为图书序号
    {
        bookList[bookCount].setBook(bookCount);
    }
    int searchISBN(string target, bool mode) //图书搜索功能1：ISBN/ISSN。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<int> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookCount; i++)
        {
            if (kmp(bookList[i].num, target))
            {
                candidate.push_back(i);
            }
        }
        if (candidate.size() == 0)
        {
            cout << "没有找到匹配此ISBN/ISSN的书籍。\n";
            return -1;
        }
        cout << "找到" << candidate.size() << "个序号符合的书籍，列表如下：\n";
        for (int i = 0; i < candidate.size(); i++)
        {
            cout << i + 1 << '.' << fixed << setw(16) << left << "书名：" << bookList[candidate[i]].title << ' 出版物号 ISBN/ISSN：' << bookList[candidate[i]].num << '\n';
        }
        if (mode == 0)
        {
            cout << "请从上面的列表里查阅您想找到的书籍。\n";
            return 0;
        }
        if (mode == 1)
        {
            cout << "请输入想借阅的书籍序号: ";
            int temp;
            cin >> temp;
            return candidate[temp - 1];
        }
    }
    int searchTitle(string target, bool mode) //图书搜索功能2：标题。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<int> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookCount; i++)
        {
            if (kmp(bookList[i].title, target))
            {
                candidate.push_back(i);
            }
        }
        if (candidate.size() == 0)
        {
            cout << "没有找到匹配此书名的书籍。\n";
            return -1;
        }
        cout << "找到" << candidate.size() << "个书名匹配的书籍，列表如下：\n";
        for (int i = 0; i < candidate.size(); i++)
        {
            cout << i + 1 << '.' << fixed << setw(16) << left << "书名：" << bookList[candidate[i]].title << ' 出版物号 ISBN/ISSN：' << bookList[candidate[i]].num << '\n';
        }
        if (mode == 0)
        {
            cout << "请从上面的列表里查阅您想找到的书籍。\n";
            return 0;
        }
        if (mode == 1)
        {
            cout << "请输入想借阅的书籍序号: ";
            int temp;
            cin >> temp;
            return candidate[temp - 1];//这个才是真正的书籍序号
        }
    }
    int searchAuthor(string target, bool mode) //图书搜索功能3：作者。作者名必须精确匹配。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<pair<Book,int>> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookCount; i++)
        {
            if (bookList[i].author==target)
            {
                candidate.push_back(pair<Book,int>(bookList[i],i));
            }
        }
        sort(candidate.begin(), candidate.end()); //运算符重载过啦，根据名称排序
        if (candidate.size() == 0)
        {
            cout << "没有找到由此作者撰写的书籍。\n";
            return -1;
        }
        cout << "找到" << candidate.size() << "个该作者出版的书籍，列表如下：\n";
        for (int i = 0; i < candidate.size(); i++)
        {
            cout << i + 1 << '.' << fixed << setw(16) << left << "书名：" << candidate[i].first.title << ' 出版物号 ISBN/ISSN：' << candidate[i].first.num << '\n';
        }
        if (mode == 0)
        {
            cout << "请从上面的列表里查阅您想找到的书籍。\n";
            return 0;
        }
        if (mode == 1)
        {
            cout << "请输入想借阅的书籍序号: ";
            int temp;
            cin >> temp;
            return candidate[temp-1].second;
        }
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
bool kmp(string a, string b)
{
    int lena = a.length(), lenb = b.length(), startPos = 0, searchPos = 0;
    if (lena > lenb)
    {
        cout << "错误:请输入搜索对象的全部或一部分。\n";
        return false;
    }
    if (a == b)
    {
        return true;
    }
    for (startPos = 0; startPos <= lenb - lena; startPos++)
    {
        for (searchPos = 0; searchPos < lena; searchPos++)
        {
            if (a[searchPos] != b[startPos + searchPos])
            {
                startPos += searchPos;
                break;
            }
        }
        if (searchPos == lena)
        {
            return true;
        }
    }
    return false;
}