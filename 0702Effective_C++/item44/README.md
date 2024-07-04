在 C++ 中，模板可以生成高效、类型安全的代码，但也可能导致代码膨胀（code bloat），即由于模板实例化生成了大量重复代码，增加了编译时间和二进制文件的大小。**Item 44: Factor parameter-independent code out of templates** 的目的是减少这种代码膨胀，通过将不依赖于模板参数的代码从模板中分离出来，以减少重复代码的生成。

### 示例和解释

假设我们有一个简单的模板类来处理数组：

```cpp
template <typename T>
class Array {
public:
    Array(int size) : size_(size), data_(new T[size]) {}

    ~Array() {
        delete[] data_;
    }

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
    T* data_;
};
```

这个模板类的所有成员函数都依赖于模板参数 `T`。如果我们有很多不同类型的 `Array` 实例，那么每个类型都会生成一个独立的 `fill` 和 `print` 函数，这会导致代码膨胀。

### 优化：提取与模板参数无关的代码

为了减少代码膨胀，我们可以将与模板参数无关的代码提取到一个非模板基类中。下面是如何实现的：

```cpp
#include <iostream>

// 非模板基类，处理与模板参数无关的代码
class ArrayBase {
public:
    ArrayBase(int size) : size_(size) {}

    virtual ~ArrayBase() {}

    void print() const {
        for (int i = 0; i < size_; ++i) {
            printElement(i);
        }
        std::cout << std::endl;
    }

protected:
    virtual void printElement(int index) const = 0;

    int size_;
};

// 模板派生类
template <typename T>
class Array : public ArrayBase {
public:
    Array(int size) : ArrayBase(size), data_(new T[size]) {}

    ~Array() {
        delete[] data_;
    }

    void fill(const T& value) {
        for (int i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

protected:
    void printElement(int index) const override {
        std::cout << data_[index] << " ";
    }

private:
    T* data_;
};

int main() {
    Array<int> intArray(5);
    intArray.fill(1);
    intArray.print();

    Array<double> doubleArray(5);
    doubleArray.fill(2.5);
    doubleArray.print();

    return 0;
}
```

### 解释

- `ArrayBase` 是一个非模板基类，包含与模板参数无关的 `print` 方法。
- `ArrayBase` 有一个纯虚函数 `printElement`，由派生类实现，以打印数组中的元素。
- `Array` 是一个模板类，继承自 `ArrayBase`。它实现了 `printElement` 函数来打印具体类型的元素。
- 通过这种方式，`ArrayBase` 中的代码只会生成一次，而不是为每个模板实例生成，减少了代码膨胀。

### 总结

通过将与模板参数无关的代码提取到非模板基类中，可以减少重复代码的生成，从而减少代码膨胀。这种技术可以提高代码的可维护性，减少编译时间和生成的二进制文件大小，是编写高效 C++ 模板代码的一种重要技巧。