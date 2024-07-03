#include <iostream>

// 通用模板
template <typename T1, typename T2>
class MyClass {
public:
    void display() {
        std::cout << "General template" << std::endl;
    }
};

// 部分特化：第二个模板参数固定为 int
template <typename T1>
class MyClass<T1, int> {
public:
    void display() {
        std::cout << "Partial specialization: second parameter is int" << std::endl;
    }
};

// 部分特化：两个模板参数相同
template <typename T>
class MyClass<T, T> {
public:
    void display() {
        std::cout << "Partial specialization: both parameters are the same type" << std::endl;
    }
};

int main() {
    MyClass<char, double> obj1;
    MyClass<char, int> obj2;
    MyClass<int, int> obj3;

    obj1.display(); // 输出 "General template"
    obj2.display(); // 输出 "Partial specialization: second parameter is int"
    obj3.display(); // 输出 "Partial specialization: both parameters are the same type"

    return 0;
}
