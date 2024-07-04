#include <iostream>

// 模板元编程计算阶乘
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// 基本情况
template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;  // 输出 120
    std::cout << "Factorial of 10: " << Factorial<10>::value << std::endl; // 输出 3628800
    return 0;
}
