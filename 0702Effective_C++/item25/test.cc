#include <iostream>
#include <utility>  // std::swap

class MyClass {
public:
    MyClass(int value) : value_(value) {}

    // 成员 swap 函数
    void swap(MyClass& other) noexcept {
        using std::swap;
        swap(value_, other.value_);
    }

    void print() const {
        std::cout << "Value: " << value_ << std::endl;
    }

private:
    int value_;
};

// 非成员 swap 函数
void swap(MyClass& a, MyClass& b) noexcept {
    a.swap(b);
}

// 特化 std::swap
namespace std {
    template <>
    void swap(MyClass& a, MyClass& b) noexcept {
        a.swap(b);
    }
}

int main() {
    MyClass obj1(1);
    MyClass obj2(2);

    std::cout << "Before swap:" << std::endl;
    obj1.print();
    obj2.print();

    // 使用自定义的 swap
    swap(obj1, obj2);

    std::cout << "After swap:" << std::endl;
    obj1.print();
    obj2.print();

    // 使用 std::swap
    std::swap(obj1, obj2);

    std::cout << "After std::swap:" << std::endl;
    obj1.print();
    obj2.print();

    return 0;
}
