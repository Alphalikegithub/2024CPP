#include <iostream>

template <typename T>
class Container {
public:
    // 嵌套类型的别名
    typedef typename T::ValueType ValueType;

    void showValue(const ValueType& value) {
        std::cout << "Value: " << value << std::endl;
    }
};

// 一个具有嵌套类型的类
class Data {
public:
    typedef int ValueType;
};

int main() {
    Container<Data> container;
    container.showValue(42);  // 输出 "Value: 42"
    return 0;
}
