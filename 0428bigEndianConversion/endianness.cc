#include <iostream>
#include <stdint.h>

int main() {
  union {
    uint32_t n;
    char bytes[4];
  } u;

  u.n = 0x12345678;

  if (u.bytes[0] == 0x12) {
    std::cout << "大端模式" << std::endl;
  } else {
    std::cout << "小端模式" << std::endl;
  }

  return 0;
}
