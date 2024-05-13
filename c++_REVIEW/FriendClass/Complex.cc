#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Complex
{
public:
    Complex(double dreal = 0,double dimag = 0)
    :_dreal(dreal)
    ,_dimag(dimag)
    {
        cout << "Complex(double  = 0,double  = 0)" << endl;
    }
    //获取私有成员变量
    double getReal() const
    {
        return _dreal;
    }
    double getImag() const
    {
        return _dimag;
    }
    void print()
    {
        cout << _dreal << "+" << _dimag << "i" << endl;
    }
    ~Complex()
    {
        cout << "~Complex" << endl;
    }
private:
    double _dreal;
    double _dimag;
};

Complex operator+(const Complex &lhs,const Complex &rhs)
{
    //return lhs.getReal() + rhs.getReal(),lhs.getImag() + rhs.getImag();
    return Complex(lhs.getReal() + rhs.getReal(), lhs.getImag() + rhs.getImag());
}
void test()
{
    Complex complex1(3,4);
    cout << "complex1 =";
    complex1.print();
    Complex complex2(5,6);
    cout << "complex2 =";
    complex2.print();
    Complex complex3;
    complex3 = complex1 + complex2;
    cout << "complex3 =";
    complex3.print();
}

int main(int argc,char **argv)
{
   
    test();
    return 0;
}