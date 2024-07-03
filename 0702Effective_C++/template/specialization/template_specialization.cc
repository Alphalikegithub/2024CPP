#include <iostream>

// 通用模板
template <typename T>
class MyClass {
public:
    void display() {
        std::cout << "General template" << std::endl;
    }
};

// 模板特化
template <>
class MyClass<int> {
public:
    void display() {
        std::cout << "Specialized template for int" << std::endl;
    }
};

int main() {
    MyClass<double> obj1;
    MyClass<int> obj2;

    obj1.display(); // 输出 "General template"
    obj2.display(); // 输出 "Specialized template for int"

    return 0;
}
