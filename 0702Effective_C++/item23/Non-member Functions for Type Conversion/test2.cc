#include <iostream>

class Complex {
public:
  Complex(double real, double imag) : real_(real), imag_(imag) {}

  friend Complex operator+(const Complex& lhs, const Complex& rhs);
  friend Complex operator+(const Complex& lhs, double rhs); // 新增
  friend Complex operator+(double lhs, const Complex& rhs); // 新增

  void print() const {
    std::cout << "(" << real_ << ", " << imag_ << "i)" << std::endl;
  }

private:
  double real_;
  double imag_;
};

// 非成员加法函数
Complex operator+(const Complex& lhs, const Complex& rhs) {
  return Complex(lhs.real_ + rhs.real_, lhs.imag_ + rhs.imag_);
}

Complex operator+(const Complex& lhs, double rhs) {
  return Complex(lhs.real_ + rhs, lhs.imag_); // 处理 Complex + double
}

Complex operator+(double lhs, const Complex& rhs) {
  return Complex(lhs + rhs.real_, rhs.imag_); // 处理 double + Complex
}

int main() {
  Complex a(1.0, 2.0);
  Complex b = a + 2.5; // 使用 Complex::Complex(double, double)
  Complex c = 2.5 + a; // 使用 Complex::Complex(double, double)
  b.print();
  c.print();
  return 0;
}
