#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::unique_ptr;
void test()
{
    int *pInt = new int(10);
    unique_ptr<int> ap(pInt);
    cout << "pInt = " << pInt << endl;
    cout << "ap.get" << ap.get() << endl;
    cout << "* ap = " << *ap << endl; 

    unique_ptr<int> up3(new int(30));
    std::vector<unique_ptr<int>> vec;
    //vec.push_back(up3);
    vec.push_back(std::move(up3));//移动语义
}
int main(int argc,char **argv)
{
    test();
    return 0;
}