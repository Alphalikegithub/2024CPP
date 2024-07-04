条款20出自Scott Meyers的《Effective C++》，它建议在C++中，尽量使用传递引用（reference）来代替传值（pass by value），特别是对于大型对象或不需要修改参数的情况。这样做可以避免不必要的复制开销，并提高函数的效率。

### 为什么要使用引用而不是值传递？

1. **效率问题**：
   - 对于大型对象，传递引用比传递值更高效。因为传递引用只需传递对象的地址，而不是整个对象的副本。
   - 传递值时，会调用拷贝构造函数来复制参数，这可能涉及到动态内存分配和复杂的对象构造，影响性能。

2. **避免对象切片问题**：
   - 如果传递的是派生类对象给一个函数，而函数参数声明的是基类引用或指针，如果使用值传递，会发生对象切片（object slicing）问题，导致丢失派生类特有的信息。

3. **表达意图**：
   - 使用引用可以明确地表达函数不需要修改参数的意图。通过使用 `const` 修饰的引用（`const T&`），还可以确保函数不会意外修改传递的对象。

### 示例

以下是一个简单的示例，演示了如何使用引用替换值传递：

```cpp
#include <iostream>
#include <string>

// 通过值传递
void processByValue(std::string value) {
    // 对参数进行操作
    value += " processed";
    std::cout << "Inside processByValue: " << value << std::endl;
}

// 通过引用传递
void processByReference(const std::string& value) {
    // 对参数进行操作
    std::string modifiedValue = value + " processed";
    std::cout << "Inside processByReference: " << modifiedValue << std::endl;
}

int main() {
    std::string data = "Original Data";

    // 值传递示例
    processByValue(data); // 复制 data 到 processByValue，产生额外的复制开销
    std::cout << "After processByValue: " << data << std::endl; // data 未被修改

    // 引用传递示例
    processByReference(data); // 通过引用传递 data，避免了额外的复制开销
    std::cout << "After processByReference: " << data << std::endl; // data 未被修改

    return 0;
}
```

在这个示例中：

- `processByValue` 函数通过值传递参数 `std::string value`，会复制 `data` 的内容到 `value`，修改 `value` 不影响 `data`。
- `processByReference` 函数通过常量引用 `const std::string& value`，直接引用 `data`，避免了复制开销，同时保证了 `data` 的不可修改性。

### 注意事项

- 当函数需要修改参数时，应该使用非常量引用 `T&`，而不是 `const T&`。
- 使用引用传递时，应该确保被引用的对象在函数调用期间是有效的，避免悬垂引用（dangling references）问题。

通过遵循条款20的建议，尽量使用引用传递来替代值传递，可以提高代码的效率和清晰度，尤其在处理大型对象或需要避免不必要复制开销的情况下更为重要。

在你提供的示例中，`processByReference` 函数的定义如下：

```cpp
void processByReference(const std::string& value) {
    std::string modifiedValue = value + " processed";
    std::cout << "Inside processByReference: " << modifiedValue << std::endl;
}
```

在这个函数中，参数 `value` 被声明为 `const std::string&`，即常量引用。这意味着在函数内部，`value` 是一个对实参 `data` 的引用，但是通过这个引用不能修改实参 `data` 的值。

### 为什么 `data` 没有被修改？

1. **常量引用的作用**：
   - `const std::string& value` 中的 `const` 关键字表明，函数 `processByReference` 承诺不会修改传递给它的参数 `value`。即使在函数内部对 `value` 进行操作，例如拼接字符串，生成的新字符串赋给了 `modifiedValue`，但这并不影响原始的 `data`。

2. **局部变量**：
   - 在 `processByReference` 函数中，`modifiedValue` 是一个局部变量，它存储了修改后的结果。修改 `modifiedValue` 不会影响传递给函数的 `value` 或者 `data`。

3. **传递方式**：
   - 在主函数中调用 `processByReference(data)` 时，`data` 被传递给 `processByReference`，但由于是通过常量引用传递，所以在函数内部对 `value` 的任何修改都不会反映到 `data`。

### 示例演示

为了更好地理解，让我们看一下在 `main()` 函数中如何调用 `processByReference` 函数：

```cpp
int main() {
    std::string data = "Original Data";

    // 引用传递示例
    processByReference(data); // 通过引用传递 data，避免了额外的复制开销
    std::cout << "After processByReference: " << data << std::endl; // data 未被修改

    return 0;
}
```

在这个示例中，`data` 在调用 `processByReference` 之后仍然保持其原始值 "Original Data"，这是因为 `processByReference` 函数只是通过常量引用访问 `data`，而没有修改它。