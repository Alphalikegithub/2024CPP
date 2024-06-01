#include <iostream>
#include <cmath>



int main(){
    // 椭球参数
    const double a = 6378137.0; // 长半轴
    const double f = 1 / 298.257222101; // 扁率
    const double e2 = 2 * f - f * f; // 第一偏心率的平方
    const double b1 = a * (1 - f); // 短半轴
    std::cout << b1 << std::endl;
    const double b2 = a * sqrt(1 - e2); // 短半轴
    std::cout << b2 << std::endl;
}