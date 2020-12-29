#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <iomanip>
using namespace std;
bool kmp(string a, string b);
struct logRecord //在馆记录
{
    int time; //时间
    int id;   //人员ID
    logRecord(int t, int i) : time(t), id(i) {}
};
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
    Book(const int bookCount)
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
        cout << "三级分类(如A751/6 1): ";
        getline(cin, category);
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
    bool operator<(const Book &another) const //重载小于运算符，实现基于标题的比较大小
    {
        return this->title < another.title;
    }
};
class repo //书库
{
private:
    vector<Book> bookList;    //图书列表
    vector<logRecord> logRec; //
public:
    void borrow(int target)
    {
    }
    void add() //增加图书功能
    {
        bookList.push_back(bookList.size() + 1);
    }
    // void modify(int num) //修改图书功能，num为图书序号
    // {
    //     bookList[bookCount].setBook_manual(bookCount);
    // }
    int searchISBN(string target, bool mode) //图书搜索功能1：ISBN/ISSN。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<int> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookList.size(); i++)
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
            cout << i + 1 << '.' << fixed << setw(16) << left << "书名：" << bookList[candidate[i]].title << " 出版物号 ISBN/ISSN：" << bookList[candidate[i]].num << '\n';
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
        for (int i = 0; i < bookList.size(); i++)
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
            cout << i + 1 << '.' << fixed << setw(16) << left << "书名：" << bookList[candidate[i]].title << " 出版物号 ISBN/ISSN：" << bookList[candidate[i]].num << '\n';
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
            return candidate[temp - 1]; //这个才是真正的书籍序号
        }
    }
    int searchAuthor(string target, bool mode) //图书搜索功能3：作者。作者名必须精确匹配。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<pair<Book, int>> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookList.size(); i++)
        {
            if (bookList[i].author == target)
            {
                candidate.push_back(pair<Book, int>(bookList[i], i));
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
            cout << i + 1 << '.' << fixed << setw(16) << left << "书名：" << candidate[i].first.title << " 出版物号 ISBN/ISSN：" << candidate[i].first.num << '\n';
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
            return candidate[temp - 1].second;
        }
    }
    int searchCategory(string target, bool mode) //根据类别的搜索功能。
    {
        vector<pair<Book, int>> candidate;
        for (int i = 0; i < bookList.size(); i++)
        {
            if (kmp(bookList[i].category, target))
            {
                candidate.push_back(pair<Book, int>(bookList[i], i));
            }
        }
        if (candidate.size() == 0)
        {
            cout << "书库中没有您想找到的分类。\n";
        }
        sort(candidate.begin(), candidate.end());
        cout << "找到了符合该分类的" << candidate.size() << "本书。\n";
        int i;
        for (i = 0; i * 30 < candidate.size(); i++)
        {
            cout << "第" << i * 30 + 1 << ' - ' << (i + 1) * 30 << "本:\n";
            for (int j = i * 30; j <= (i + 1) * 30; j++)
            {
                cout << j + 1 << " : " << candidate[j].first.title << " ISBN/ISSN: " << candidate[j].first.num << '\n';
            }
            if (mode == 1)
            {
                cout << "请输入您要查阅的书籍序号。如未找到，请输入-1，翻阅下一页:";
                int temp;
                cin >> temp;
                if (temp != -1)
                {
                    return candidate[temp].second; //返回书籍的真正序号
                }
            }
            else
            {
                cout << "如果您未找到您要找的书，请输入-1；如果找到，请输入1:";
                int temp;
                cin >> temp;
                if (temp == -1)
                {
                    return 0;
                }
            }
        }
        for (int j = (i - 1) * 30; j < candidate.size(); j++)
        {
            cout << j + 1 << " : " << candidate[j].first.title << " ISBN/ISSN: " << candidate[j].first.num << '\n';
        }
        if (mode == 1)
        {
            cout << "请输入您要查阅的书籍序号。如未找到，请输入-1退出";
            int temp;
            cin >> temp;
            if (temp != -1)
            {
                return candidate[temp].second; //返回书籍的真正序号
            }
        }
        else
        {
            cout << "如果您未找到您要找的书，请输入-1以退出；如果找到，请输入1:";
            int temp;
            cin >> temp;
            if (temp == -1)
            {
                return 0;
            }
        }
    }
    friend class account;
};
class account
{
private:
    int username;           //用户名
    int password;           //密码
    list<int> borrowedBook; //借了的书，使用链表存储，好删除
public:
    void borrowBook(repo &r)
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
        }
        return;
    }
    void searchBook(repo &r);
};
class student : public account
{
};
class admin : public account
{
};
int main()
{
    repo library;
    vector<student> studentList;
    vector<admin> adminList;
    return 0;
}
bool kmp(string a, string b) //KMP是一种字符串匹配算法，可以实现b部分匹配a的查找。
{
    int lena = a.length(), lenb = b.length(), startPos = 0, searchPos = 0;
    if (lena > lenb)
    {
        cerr << "错误:请输入搜索对象的全部或一部分。\n";
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