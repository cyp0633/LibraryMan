#ifndef _REPO_H_INCLUDED
#define _REPO_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "Book.h"
#include "KMP.h"
#include "error.h"
struct logRecord //在馆记录
{
    time_t time;      //时间
    long long int id; //人员ID
    bool type;        //账户类型，1是管理员
    logRecord(const time_t &t, const long long int &i, const bool &tp) : time(t), id(i), type(tp) {}
};
struct borrowRecord //借阅记录
{
    time_t time;
    long long int id;
    bool type;
    int bookNum;
    borrowRecord(const time_t &t, const long long int &i, const int &n, const bool &tp) : time(t), id(i), bookNum(n), type(tp) {}
};
class repo //书库
{
private:
    vector<Book> bookList;       //图书列表
    vector<logRecord> logRec;    //在馆记录
    vector<borrowRecord> borRec; //借阅记录
public:
    void add() //增加图书功能
    {
        bookList.push_back(Book(1));
    }
    void modify(int num) //修改图书功能，num为图书序号
    {
        bookList[num].setBook_manual();
    }
    int searchISBN(string target, bool mode) //图书搜索功能1：ISBN/ISSN。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<int> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookList.size(); i++)
        {
            if ((!bookList[i].deleted) && kmp(target, bookList[i].num))
            {
                candidate.push_back(i);
            }
        }
        if (candidate.size() == 0)
        {
            std::cout << "没有找到匹配此ISBN/ISSN的书籍。\n";
            return -1;
        }
        std::cout << "找到" << candidate.size() << "个序号符合的书籍，列表如下：\n";
        for (int i = 0; i < candidate.size(); i++)
        {
            std::cout << setw(4) << left << i + 1 << '.' << "书名：" << setw(60) << left << bookList[candidate[i]].title << " 出版物号 ISBN/ISSN：" << bookList[candidate[i]].num << '\n';
        }
        if (mode == 0)
        {
            std::cout << "请从上面的列表里查阅您想找到的书籍。\n";
            return 0;
        }
        else
        {
            std::cout << "请输入想借阅的书籍序号: ";
            int temp = getInt(temp);
            return candidate[temp - 1];
        }
    }
    int searchTitle(string target, bool mode) //图书搜索功能2：标题。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<int> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookList.size(); i++)
        {
            if (kmp(target, bookList[i].title) && !bookList[i].deleted)
            {
                candidate.push_back(i);
            }
        }
        if (candidate.size() == 0)
        {
            std::cout << "没有找到匹配此书名的书籍。\n";
            return -1;
        }
        std::cout << "找到" << candidate.size() << "个书名匹配的书籍，列表如下：\n";
        for (int i = 0; i < candidate.size(); i++)
        {
            std::cout << setw(4) << left << i + 1 << '.' << "书名：" << setw(60) << left << bookList[candidate[i]].title << " 出版物号 ISBN/ISSN：" << bookList[candidate[i]].num << '\n';
        }
        if (mode == 0)
        {
            std::cout << "请从上面的列表里查阅您想找到的书籍。\n";
            return 0;
        }
        else
        {
            cout << "请输入想查阅的书籍序号: ";
            int temp = getInt(temp);
            return candidate[temp - 1]; //这个才是真正的书籍序号
        }
    }
    int searchAuthor(string target, bool mode) //图书搜索功能3：作者。作者名必须精确匹配。如果由借阅函数调用，mode=1，还会返回借阅的书籍序号；如果单纯是查找，mode=0
    {
        vector<pair<Book, int>> candidate; //这个vector用于保存符合条件的书籍
        for (int i = 0; i < bookList.size(); i++)
        {
            if (bookList[i].author == target && !bookList[i].deleted)
            {
                candidate.push_back(pair<Book, int>(bookList[i], i));
            }
        }
        stable_sort(candidate.begin(), candidate.end()); //运算符重载过啦，根据名称排序
        if (candidate.size() == 0)
        {
            std::cout << "没有找到由此作者撰写的书籍。\n";
            return -1;
        }
        std::cout << "找到" << candidate.size() << "个该作者出版的书籍，列表如下：\n";
        for (int i = 0; i < candidate.size(); i++)
        {
            std::cout << setw(4) << left << i + 1 << '.' << "书名：" << setw(60) << left << candidate[i].first.title << " 出版物号 ISBN/ISSN：" << candidate[i].first.num << '\n';
        }
        if (mode == 0)
        {
            std::cout << "请从上面的列表里查阅您想找到的书籍。\n";
            return 0;
        }
        else
        {
            std::cout << "请输入想借阅的书籍序号: ";
            int temp = getInt(temp);

            return candidate[temp - 1].second;
        }
    }
    int searchCategory(string target, bool mode) //根据类别的搜索功能。
    {
        vector<pair<Book, int>> candidate;
        for (int i = 0; i < bookList.size(); i++)
        {
            if (kmp(target, bookList[i].category) && !bookList[i].deleted)
            {
                candidate.push_back(pair<Book, int>(bookList[i], i));
            }
        }
        if (candidate.size() == 0)
        {
            std::cout << "书库中没有您想找到的分类。\n";
        }
        stable_sort(candidate.begin(), candidate.end());
        std::cout << "找到了符合该分类的" << candidate.size() << "本书。\n";
        int i;
        if (candidate.size() > 30)
        {
            for (i = 0; i * 30 < candidate.size(); i++)
            {
                std::cout << "第" << i * 30 + 1 << " - " << (i + 1) * 30 << "本:\n";
                for (int j = i * 30; j < (i + 1) * 30; j++)
                {
                    std::cout << setw(4) << left << j + 1 << " : " << setw(60) << left << candidate[j].first.title << " ISBN/ISSN: " << candidate[j].first.num << '\n';
                }
                if (mode == 1)
                {
                    std::cout << "请输入您要查阅的书籍序号。如未找到，请输入-1，翻阅下一页:";
                    int temp = getInt(temp);
                    if (temp != -1)
                    {
                        return candidate[temp - 1].second; //返回书籍的真正序号
                    }
                }
                else
                {
                    std::cout << "如果您未找到您要找的书，请输入-1；如果找到，请输入1:";
                    int temp = getInt(temp);
                    if (temp == 1)
                    {
                        return 0;
                    }
                }
            }
            for (int j = (i - 1) * 30; j < candidate.size(); j++)
            {
                std::cout << setw(4) << left << j + 1 << " : " << setw(60) << left << candidate[j].first.title << " ISBN/ISSN: " << candidate[j].first.num << '\n';
            }
        }
        else
        {
            for (int j = 0; j < candidate.size(); j++)
            {
                std::cout << setw(4) << left << j + 1 << " : " << setw(60) << left << candidate[j].first.title << " ISBN/ISSN: " << candidate[j].first.num << '\n';
            }
        }
        if (mode == 1)
        {
            std::cout << "请输入您要查阅的书籍序号。如未找到，请输入-1退出\n";
            int temp = getInt(temp);

            if (temp != -1)
            {
                return candidate[temp - 1].second; //返回书籍的真正序号
            }
            else
            {
                return -1;
            }
        }
        else
        {
            std::cout << "请输入任意数字以退出。\n";
            int temp = getInt(temp);

            return 0;
        }
    }
    void fileImport() //文件导入书籍目录
    {
        cout << "即将从books.txt导入图书目录。\n";
        ifstream bookInput;
        int originalNum = bookList.size();
        bookInput.open("NewBooks.txt", ios::in);
        string title;
        while (bookInput >> title)
        {
            bookList.push_back(Book());
            bookList.back().title = title;
            bookInput >> bookList.back().num >> bookList.back().author >> bookList.back().category >> bookList.back().remainingNum;
        }
        bookInput.close();
        cout << "已导入" << bookList.size() - originalNum << "本图书。\n";
    }
    friend class account;
    void deleteBook(int num)
    {
        bookList[num].deleted = true;
    }
    void displayLogRec(unsigned int startTime, unsigned int endTime) //查询的起止时间
    {
        vector<logRecord>::iterator i;
        if (endTime == 0)
        {
            endTime = -1;
        }
        for (i = logRec.begin(); i != logRec.end(); i++)
        {
            if (i->time >= startTime && i->time <= endTime)
            {
                std::cout << put_time(localtime(&(i->time)), "%c %Z") << " - " << setw(15) << right << i->id << "入馆\n"; //找时候做一下时间戳转换为标准时间
            }
        }
        return;
    }
    void displayBorRec(unsigned int startTime, unsigned int endTime) //查询的起止时间
    {
        vector<borrowRecord>::iterator i;
        if (endTime == 0)
        {
            endTime = -1;
        }
        for (i = borRec.begin(); i != borRec.end(); i++)
        {
            if (i->time >= startTime && i->time <= endTime)
            {
                std::cout << put_time(localtime(&(i->time)), "%c %Z") << " - " << setw(15) << right << i->id << "借走了\"" << bookList[i->bookNum].title << "\"\n"; //找时候做一下时间戳转换为标准时间
            }
        }
        return;
    }
    friend class admin;
    friend class student;
    void addLogRec(const time_t &t, const long long int &i, const bool &tp);
    void addBorRec(const time_t &t, const long long int &i, const int &n, const bool &tp);
};
void repo::addLogRec(const time_t &t, const long long int &i, const bool &tp)
{
    logRec.push_back(logRecord(t, i, tp));
    return;
}
void repo::addBorRec(const time_t &t, const long long int &i, const int &n, const bool &tp)
{
    borRec.push_back(borrowRecord(t, i, n, tp));
}
#endif