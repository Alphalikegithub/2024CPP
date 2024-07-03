#include <iostream>

// 通用类模板
template <typename T>
class MyClass {
public:
    void display() {
        std::cout << "General display: " << value << std::endl;
    }

    T value;
};

// 类模板的全特化，针对 int 类型
template <>
class MyClass<int> {
public:
    void display() {
        std::cout << "Specialized display for int: " << value << std::endl;
    }

    int value;
};

int main() {
    MyClass<double> obj1;
    obj1.value = 10.5;
    obj1.display(); // 输出 "General display: 10.5"

    MyClass<int> obj2;
    obj2.value = 20;
    obj2.display(); // 输出 "Specialized display for int: 20"

    return 0;
}
