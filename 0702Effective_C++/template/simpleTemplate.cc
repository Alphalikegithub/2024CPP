#include <iostream>

// 定义一个函数模板，typename T 表示类型参数
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << max(10, 20) << std::endl;       // 输出 20，使用 int 类型
    std::cout << max(10.5, 7.3) << std::endl;    // 输出 10.5，使用 double 类型
    std::cout << max('a', 'z') << std::endl;     // 输出 z，使用 char 类型
    return 0;
}
