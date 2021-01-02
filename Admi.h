#ifndef _ADMI_H_INCLUDED_
#define _ADMI_H_INCLUDED_
#include "Account.h"
#include <iostream>
#include <vector>
using namespace std;
class admin : public account
{
public:
    admin(int n,string password):account(n,password){}
    void homepage() //管理员账户的主界面
    {
        cout << "现在登录的是管理员账户，请输入您要执行的操作对应的序号。\n1-添加图书 | 2-修改图书 | 3-搜索图书 | 4-删除图书 | 5-添加账号 | 6-修改账号 | 7-退出到主页面,输入其他数字退出登录";
        int operation;
        cin >> operation;
        switch (operation)
        {
        case 1:
            library.add();
            break;
        case 2:
            cout<<"请输入您想修改图书的编号\n";
            int num;
            cin>>num;
            library.modify(num);
            break;
        case 3:
        {
          account::searchBook(library);
        }
        case 4:
           cout<<"请输入您想删除图书的编号\n";
            cin>>num;
            library.deleteBook(num);
            break;
//添加账号
        case 5:
        cout<<"请输入您想添加的账号位置以及其位置以及其编号或学号\n";
        int id;
        cin>>num>>id;//添加的账户位置
        student one(id,"123456"); //新增的账户
         studentList.insert(studentList.begin(),one);  
            break;
//修改账号
        case 6:
        cout<<"请输入您想修改的账号位置以及其位置以及其编号或学号\n";
        cin>>num;//修改的账户位置
        account::modify();
            break;
        case 7:
        {
        homepage();
        break;
        }
        default: break;
        }
        return;
    }
};
//管理员的人数控制
vector <admin> adminList;
#endif