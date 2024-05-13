#include <iostream>
#include <set>
#include <map>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::set;
using std::pair;
using std::map;

void test()
{
    map<string,string> map1 =
    {
        {"101","长江"},
        {"102","黄河"},
        {"102","淮河"},
        pair<string,string>("103","珠江"),
        pair<string,string>("104","湘江")
    };
    pair<int,string> pair1(10,"hello");
    cout << "pair的形式: " << pair1.first << ", " << pair1.second << endl;
    for(auto &elem:map1)
    {
        cout << elem.first << ", " << elem.second << endl;
    }
    cout << "-------------" << endl;
    //map的插入操作
    //pair<map<string,string>::iterator,bool> ret = map1.insert(pair<string,string> ("111","赣江"));
    //上一条代码的前半部分都是返回类型,可以直接使用类型推导
    auto ret = map1.insert(pair<string,string> ("121","赣江"));
    //上面的语句可以再简化成
    //auto ret = map1.insert({"121","赣江"});
    if(ret.second)
    {
        cout << "插入成功，插入的值为" << ret.first->first << ", " << ret.first->second << endl;
    }
    else{
        cout << "failure" << endl;
    }
    for(auto &elem:map1)
    {
        cout << elem.first << ", " << elem.second << endl;
    }
    cout << "-------------" << endl;
    //map的下标访问运算符具备插入和修改功能
    map1["123"] = "松花江";
    for(auto &elem:map1)
    {
        cout << elem.first << ", " << elem.second << endl;
    }
    cout << "通过下标访问运算符修改后" << endl;
    map1["123"] = "黑龙江";
    for(auto &elem:map1)
    {
        cout << elem.first << ", " << elem.second << endl;
    }
}

int main(int argc,char **argv)
{

    test();
    return 0;
}