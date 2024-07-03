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

    // 声明为友元函数，使其能访问私有成员
    friend Complex operator+(double lhs, const Complex& rhs);

private:
    double real_;
    double imag_;
};

// 非成员加法函数
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real_, rhs.imag_);
}

int main() {
    Complex a(1.0, 2.0);
    Complex b = a + 2.5; // 使用 Complex::operator+(double)
    Complex c = 2.5 + a; // 使用全局 operator+(double, const Complex&)
    b.print();
    c.print();
    return 0;
}
