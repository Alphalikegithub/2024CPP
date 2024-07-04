#include <iostream>

class Complex {
public:
    Complex(double real, double imag) : real_(real), imag_(imag) {}

    // 成员函数加法
    Complex operator+(double rhs) const {
        return Complex(real_ + rhs, imag_);
    }

    void print() const {
        std::cout << "(" << real_ << ", " << imag_ << "i)" << std::endl;
    }

private:
    double real_;
    double imag_;
};

// 全局的加法函数重载，处理 double 和 Complex 类型的加法
Complex operator+(double lhs, const Complex& rhs) {
    return rhs + lhs;  // 调用成员函数
}

int main() {
    Complex a(1.0, 2.0);
    Complex b = a + 2.5; // 使用 Complex::operator+(double)
    Complex c = 2.5 + a; // 使用全局 operator+(double, const Complex&)
    b.print();
    c.print();
    return 0;
}
