#include <iostream>

// 定义一个类模板，typename T 表示类型参数
template <typename T>
class MyClass {
private:
    T data;
public:
    MyClass(T data) : data(data) {}  // 构造函数，初始化成员变量

    T getData() {
        return data;
    }
};

int main() {
    MyClass<int> intObj(10);          // 使用 int 类型
    MyClass<double> doubleObj(10.5);  // 使用 double 类型
    MyClass<std::string> stringObj("Hello"); // 使用 std::string 类型

    std::cout << intObj.getData() << std::endl;       // 输出 10
    std::cout << doubleObj.getData() << std::endl;    // 输出 10.5
    std::cout << stringObj.getData() << std::endl;    // 输出 Hello

    return 0;
}
