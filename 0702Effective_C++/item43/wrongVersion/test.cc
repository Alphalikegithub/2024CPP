template <typename T>
class Base {
public:
    void baseFunction() {
        // 基类函数实现
    }
    int baseMember;
};

template <typename T>
class Derived : public Base<T> {
public:
    void derivedFunction() {
        baseFunction();  // 错误：编译器不知道 baseFunction 是基类的成员
        int x = baseMember;  // 错误：编译器不知道 baseMember 是基类的成员
    }
};
