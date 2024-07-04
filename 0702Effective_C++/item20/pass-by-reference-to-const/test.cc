#include <iostream>
#include <string>

// 带有 const 的参数
void processByConstReference(const std::string& value) {
    std::string modifiedValue = value + " processed";
    std::cout << "Inside processByConstReference: " << modifiedValue << std::endl;
}

// 不带 const 的参数
void processByReference(std::string& value) {
    std::string modifiedValue = value + " processed";
    std::cout << "Inside processByReference: " << modifiedValue << std::endl;
}

int main() {
    std::string data = "Original Data";

    // 调用带有 const 的参数函数
    processByConstReference(data); // 通过 const 引用传递 data，不能修改它
    std::cout << "After processByConstReference: " << data << std::endl; // data 未被修改

    // 调用不带 const 的参数函数
    processByReference(data); // 通过引用传递 data，可以修改它
    std::cout << "After processByReference: " << data << std::endl; // data 被修改

    return 0;
}
