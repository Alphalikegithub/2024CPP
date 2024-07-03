#include <iostream>

// 定义一个类模板，typename T 表示类型参数，int size 表示非类型参数
template <typename T, int size>
class Array {
private:
    T arr[size]; // 固定大小的数组
public:
    int getSize() const {
        return size;
    }
};

int main() {
    Array<int, 10> intArray; // 创建一个大小为 10 的 int 数组
    Array<double, 20> doubleArray; // 创建一个大小为 20 的 double 数组

    std::cout << "Size of intArray: " << intArray.getSize() << std::endl; // 输出 10
    std::cout << "Size of doubleArray: " << doubleArray.getSize() << std::endl; // 输出 20

    return 0;
}
