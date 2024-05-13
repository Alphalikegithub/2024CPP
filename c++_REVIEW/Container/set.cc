#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::set;
using std::pair;

void test()
{
    std::set<int> number = {1,2,3,3,7,8,8,9,5,4};
    std::set<int>::iterator it;
    for(it = number.begin();it != number.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    for(auto &elem:number)
    {
        cout << elem << " ";
    }
    cout << endl;

    //在迭代器里面，end指向nullptr
    auto it2 = number.find(7);
    if(it2 == number.end())
    {
        cout << "该元素不存在" << endl;
    }
    else{
        cout << *it2 << endl;
    }
    //插入操作
    pair<set<int>::iterator,bool> ret = number.insert(10);
    if(ret.second)//bool值为true
    {
        cout << "插入成功,新插入的值为" << *ret.first << endl;
    }
    else{
        cout << "插入失败" << endl;
    }
    for(auto &elem:number)
    {
        cout << elem << " ";
    }
    cout << endl;
    auto it3 = number.begin();
    cout << "it3 = " << *it3 << endl;
}

int main(int argc,char **argv)
{

    test();
    return 0;
}