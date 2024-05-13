#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;


class Point
{
public:
Point(int ix = 0, int iy = 0)
: _ix(ix)
, _iy(iy)
{}
//...
friend ostream &operator<<(ostream &os, const Point &rhs);
private:
int _ix;
int _iy;
};
ostream &operator<<(ostream &os, const Point &rhs)
{
os << "(" << rhs._ix
<< "," << rhs._iy
<< ")";
return os;
}
void test()
{
Point pt = 1;//隐式转换
cout << "pt = " << pt << endl;
}

int main(int argc,char **argv)
{

    test();
    return 0;
}