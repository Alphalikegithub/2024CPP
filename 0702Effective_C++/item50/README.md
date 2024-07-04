## 《Effective C++》第50条：理解何时替换 `new` 和 `delete` 有意义。

### 何时考虑替换 `new` 和 `delete`

1. **性能优化**：
    - **自定义内存分配器**：对于频繁分配和释放内存的应用程序，自定义内存分配器可以显著提高性能，减少默认 `new` 和 `delete` 操作的开销。
    - **内存池**：内存池是一种维护固定大小内存块的方法。这可以减少碎片化并提高分配速度。

2. **调试和跟踪**：
    - **内存泄漏**：自定义 `new` 和 `delete` 可以帮助跟踪内存的分配和释放，便于识别内存泄漏。
    - **边界检查**：自定义分配器可以实现边界检查，捕捉缓冲区溢出和下溢。
    - **日志记录**：在内存分配和释放时添加日志记录，可以提供内存使用模式的洞察，并帮助识别问题。

3. **处理对齐需求**：
    - 一些数据结构或硬件可能需要特定的内存对齐。自定义 `new` 和 `delete` 可以强制执行这些对齐要求。

4. **嵌入式系统和特殊环境**：
    - 在受限环境（如嵌入式系统）中，内存有限，自定义内存管理对于高效操作至关重要。

### 如何替换 `new` 和 `delete`

要替换全局的 `new` 和 `delete` 操作符，可以在代码中全局定义它们：

```cpp
#include <cstdlib>
#include <iostream>

// 自定义全局 new 操作符
void* operator new(size_t size) {
    std::cout << "Custom new called, size: " << size << std::endl;
    void* p = std::malloc(size);
    if (!p) {
        throw std::bad_alloc();
    }
    return p;
}

// 自定义全局 delete 操作符
void operator delete(void* p) noexcept {
    std::cout << "Custom delete called" << std::endl;
    std::free(p);
}

// 自定义全局 new[] 操作符
void* operator new[](size_t size) {
    std::cout << "Custom new[] called, size: " << size << std::endl;
    void* p = std::malloc(size);
    if (!p) {
        throw std::bad_alloc();
    }
    return p;
}

// 自定义全局 delete[] 操作符
void operator delete[](void* p) noexcept {
    std::cout << "Custom delete[] called" << std::endl;
    std::free(p);
}
```

### 使用示例

在一个简单的类中使用自定义 `new` 和 `delete` 操作符：

```cpp
class MyClass {
public:
    int x;
    MyClass(int val) : x(val) {
        std::cout << "MyClass constructed with value: " << x << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructed" << std::endl;
    }
};

int main() {
    MyClass* p = new MyClass(42);
    delete p;

    MyClass* arr = new MyClass[2] { MyClass(1), MyClass(2) };
    delete[] arr;

    return 0;
}
```

### 注意事项

1. **异常安全**：确保自定义 `new` 和 `delete` 操作符在内存分配失败时正确处理，通过抛出 `std::bad_alloc`。
2. **线程安全**：如果应用程序是多线程的，确保自定义内存管理是线程安全的。
3. **开销**：注意添加日志或调试信息会引入开销。可以使用条件编译或运行时标志来启用或禁用这些功能。

通过理解并仔细应用这些概念，在内存管理方面，你可以增强程序的性能、健壮性和可调试性。
