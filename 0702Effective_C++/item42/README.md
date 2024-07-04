《Effective C++》第42条讨论了 `typename` 关键字在 C++ 中的两种不同含义：用来声明类型和用来指示嵌套依赖类型。这一条对于编写和理解模板代码尤其重要。

### 1. 声明类型

在定义模板时，`typename` 用于声明一个模板参数是一个类型。例如：

```cpp
template <typename T>
class MyClass {
    T data;
};
```

在这个例子中，`typename T` 表示 `T` 是一个类型参数。`typename` 可以与 `class` 关键字互换使用，效果是相同的：

```cpp
template <class T>
class MyClass {
    T data;
};
```

### 2. 指示嵌套依赖类型

当模板类依赖于另一个模板参数时，`typename` 用于指示嵌套类型。这在模板类的定义中尤为重要，因为编译器需要明确区分类型和其他名字（例如变量名或函数名）。考虑以下例子：

```cpp
template <typename T>
class Outer {
public:
    typedef typename T::InnerType InnerType; // 指示 InnerType 是类型
};
```

在这里，`typename T::InnerType` 告诉编译器 `InnerType` 是 `T` 的嵌套类型。如果不加 `typename`，编译器会认为 `InnerType` 是一个静态成员变量或成员函数。

### 例子

以下是一个详细的例子来说明这两种用法：

```cpp
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
```

在这个例子中：
1. `template <typename T>` 表示 `T` 是一个类型参数。
2. `typedef typename T::ValueType ValueType` 告诉编译器 `ValueType` 是 `T` 中定义的嵌套类型。

### 需要注意的地方

当你在模板类中使用嵌套依赖类型时，如果不加 `typename`，编译器会产生错误。例如：

```cpp
template <typename T>
class Outer {
public:
    typedef T::InnerType InnerType; // 错误，缺少 typename
};
```

这个代码会产生编译错误，因为编译器认为 `InnerType` 是一个成员变量或成员函数，而不是类型。

### 结论

`typename` 在 C++ 中有两种主要用途：
1. 声明模板参数是一个类型。
2. 指示嵌套依赖类型是一个类型而不是成员变量或成员函数。

理解这两种用法对于正确编写和理解模板代码至关重要。通过正确使用 `typename`，你可以避免编译错误，并使你的模板代码更加清晰和易于维护。