#include <iostream>
#include <arpa/inet.h>

int main() {
  // 定义无符号短整型变量 s 并初始化为 0x1234
  unsigned short s = 0x1234;

  // 输出 s 的原始值
  std::cout << "s = " << std::hex << s << std::endl;

  // 将 s 转换为网络字节顺序并输出
  unsigned short s_network = htons(s);
  std::cout << "htons(s) = " << std::hex << s_network << std::endl;

  // 定义无符号长整型变量 i 并初始化为 0x12345678
  unsigned int i = 0x12345678;

  // 输出 i 的原始值
  std::cout << "i = " << std::hex << i << std::endl;

  // 将 i 转换为网络字节顺序并输出
  unsigned int i_network = htonl(i);
  std::cout << "htonl(i) = " << std::hex << i_network << std::endl;

  return 0;
}
