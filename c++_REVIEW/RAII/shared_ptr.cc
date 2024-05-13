#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::shared_ptr;
void test()
{
    int *pInt = new int(10);
    shared_ptr<int> sp(pInt);
    cout << "pInt = " << pInt << endl;
    cout << "sp.get" << sp.get() << endl;
    cout << "* sp = " << *sp << endl; 
    //打印引用计数
    cout << "sp.use_count() = " << sp.use_count() << endl;
    cout << endl;
    shared_ptr<int> sp2(sp);//可以进行复制
    cout << "*sp2 = " << *sp2 <<endl;
    cout << "sp2.use_count() = " << sp2.use_count() << endl;
    shared_ptr<int> up3(new int(30));
    std::vector<shared_ptr<int>> vec;
    //vec.push_back(up3);
    vec.push_back(std::move(up3));//移动语义
    cout << endl << endl;
    cout << "最终的引用次数：" << endl;
    cout << "sp.use_count() = " << sp.use_count() << endl;
    cout << "sp2.use_count() = " << sp2.use_count() << endl;
}
int main(int argc,char **argv)
{
    test();
    return 0;
}