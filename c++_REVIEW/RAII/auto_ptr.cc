#include <iostream>
#include <stdio.h>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;
void test()
{
    int *pInt = new int(10);
    auto_ptr<int> ap(pInt);
    cout << "pInt = " << pInt << endl;
    cout << "ap.get" << ap.get() << endl;
    cout << "* ap = " << *ap << endl; 
}
int main(int argc,char **argv)
{
    test();
    return 0;
}