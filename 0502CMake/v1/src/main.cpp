#include <iostream>
#include <stdio.h>
#include "head.h"

using std::cout;
using std::endl;
int main()
{
    int a = 20;
    int b = 12;
    cout << "a = " << a << ",b= " << b << endl;
    cout << "a + b = " << add(a,b) << endl;
    cout << "a - b = " << subtract(a,b) << endl;
    cout << "a * b = " << multiply(a,b) << endl;
    cout << "a / b = " << divide(a,b) << endl;

    return 0;
}