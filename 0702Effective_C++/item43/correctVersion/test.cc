#include <iostream>

template <typename T>
class Base {
public:
    void baseFunction() {
        std::cout << "Base function" << std::endl;
    }
    int baseMember;
};

template <typename T>
class Derived : public Base<T> {
public:
    void derivedFunction() {
        this->baseFunction();  // 方法一：使用 this->
        int x = this->baseMember;  // 方法一：使用 this->

        Base<T>::baseFunction();  // 方法二：使用 Base<T>::
        x = Base<T>::baseMember;  // 方法二：使用 Base<T>::

        baseFunction();  // 方法三：引入基类成员后直接使用
        x = baseMember;  // 方法三：引入基类成员后直接使用
    }
    using Base<T>::baseFunction;  // 方法三：引入基类成员
    using Base<T>::baseMember;  // 方法三：引入基类成员
};

int main() {
    Derived<int> d;
    d.derivedFunction();
    return 0;
}
