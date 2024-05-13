#include <iostream>
#include <math.h>

using std::cout;
using std::endl;
using std::cin;
//抽象类
class Figure
{
public:
    virtual void display() = 0;
    virtual double area() = 0;//纯虚函数

};
//圆形
class Circle
:public Figure
{
public:
    Circle(double radius = 0)
    :_radius(radius)
    {

    }
    void display() override
    {
        cout << "Circle: ";
    }
    double area() override
    {
        return 3.14 * _radius * _radius;
    }
private:
    double _radius;

};
//长方形
class Rectangle
:public Figure
{
public:
    Rectangle(double length = 0,double width = 0)
    :_length(length)
    ,_width(width)
    {

    }
    void display() override
    {
        cout << "Reactangle : ";
    }
    double area() override
    {
        return _length * _width ;
    }
    ~Rectangle()
    {
        cout << "~Reactangle()" << endl;
    }
private:
    double _length;
    double _width;
};
//矩形
class Triangle
:public Figure
{
public:
    Triangle(double a = 0,double b =0,double c = 0)
    :_a(a)
    ,_b(b)
    ,_c(c)
    {
        
    }
    void display() override
    {
        cout << "Triangle: ";
    }
    double area() override
    {
        //海伦公式
        double tmp = (_a + _b + _c)/2;
        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }
private:
    double _a;
    double _b;
    double _c;
};
void func(Figure * pFigure)
{
    pFigure->display();
    cout << "的面积" << pFigure->area() << endl;
}

int main(int argc,char **argv)
{
    Circle circle(10);
    Rectangle rectangle(10,20);
    Triangle triangle(3,4,5);
    
    func(&circle);
    func(&rectangle);
    func(&triangle);
    return 0;
}