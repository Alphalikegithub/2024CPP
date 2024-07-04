#include <iostream>
#include <vector>

template <typename T>
class Array {
public:
    // 构造函数，使用初始化列表初始化成员变量
    Array(int size) : size_(size), data_(size) {}

    void fill(const T& value) {
        for (int i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    void print() const {
        for (int i = 0; i < size_; ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    int size_;
    std::vector<T> data_;
};

int main() {
    Array<int> intArray(5);    // 创建一个包含5个int元素的数组
    intArray.fill(1);          // 将所有元素填充为1
    intArray.print();          // 打印数组内容

    Array<double> doubleArray(5);  // 创建一个包含5个double元素的数组
    doubleArray.fill(2.5);         // 将所有元素填充为2.5
    doubleArray.print();           // 打印数组内容

    return 0;
}
