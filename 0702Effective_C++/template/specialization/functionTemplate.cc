#include <iostream>

// 通用模板
template <typename T>
void print(T value) {
    std::cout << "General template: " << value << std::endl;
}

// 完全特化：特化 print<int>
template <>
void print<int>(int value) {
    std::cout << "Specialized template for int: " << value << std::endl;
}

int main() {
    print(10);          // 输出 "Specialized template for int: 10"
    print(10.5);        // 输出 "General template: 10.5"
    print("Hello");     // 输出 "General template: Hello"

    return 0;
}
