//自定义头文件
#include"Book.h"
#include"Repo.h"
#include"Account.h"
#include"Student.h"
#include"Admi.h"
#include"KMP.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <ctime>
#include <iomanip>
#include <regex>
using namespace std;
int main()
{
    cout << "您想要导入账号数据，还是创建一个新设置？\n当然，并没有做导入工具，所以只能重新设置账户。";
    cout << "需要创建第一个管理员账户才可继续。\n";
    adminList.push_back(admin());
    cout << "现在将登入这个账号……";
    adminList[0].homepage();
    return 0;
}
