#include <iostream>
#include <cmath>

// 椭球参数
const double a = 6378137.0; // 长半轴
const double f = 1 / 298.257222101; // 扁率
const double e2 = 2 * f - f * f; // 第一偏心率的平方
const double b = a * (1 - f); // 短半轴

struct Coordinates {
    double latitude;
    double longitude;
    double height;
};

struct Cartesian {
    double x;
    double y;
    double z;
};

// 将经纬度转换为空间直角坐标
Cartesian geodeticToCartesian(const Coordinates& coord) {
    /* 
    在地理空间计算中，很多公式和计算都是基于弧度而非度数的。具体来说：
    经度和纬度通常以度数的形式给出，但在大多数地理空间计算中，需要将其转换为弧度。这是因为三角函数等计算通常采用弧度作为单位。
    在 C++ 中，标准的三角函数库 <cmath> 中的函数，比如 sin()、cos()、atan2() 等，接受的是弧度作为参数，而不是度数
     */
    //将经纬度从度数转换为弧度
    double phi = coord.latitude * M_PI / 180.0;
    double lambda = coord.longitude * M_PI / 180.0;
    double h = coord.height;

    double N = a / sqrt(1 - e2 * sin(phi) * sin(phi));

    double X = (N + h) * cos(phi) * cos(lambda);
    double Y = (N + h) * cos(phi) * sin(lambda);
    double Z = (N * (1 - e2) + h) * sin(phi);

    return {X, Y, Z};
}

// 将空间直角坐标转换为经纬度
Coordinates cartesianToGeodetic(const Cartesian& cart) {
    double p = sqrt(cart.x * cart.x + cart.y * cart.y);
    double theta = atan2(cart.z * a, p * b);

    double phi = atan2(cart.z + e2 * b * pow(sin(theta), 3), p - e2 * a * pow(cos(theta), 3));
    double lambda = atan2(cart.y, cart.x);
    double N = a / sqrt(1 - e2 * sin(phi) * sin(phi));
    double h = p / cos(phi) - N;

    //将计算得到的经纬度值从弧度再转换回度数
    phi = phi * 180.0 / M_PI;
    lambda = lambda * 180.0 / M_PI;

    return {phi, lambda, h};
}

int main() {
    // 已知点的经纬度和高程
    Coordinates knownPoint = {34.0, 108.0, 100.0}; // 例：纬度34度，经度108度，高程100米

    // 已知点到目标点的相对位置向量
    Cartesian relativePosition = {100.0, 200.0, 300.0}; // 例：相对位置向量

    // 将已知点的经纬度转换为空间直角坐标
    Cartesian knownCartesian = geodeticToCartesian(knownPoint);

    // 计算目标点的空间直角坐标
    Cartesian targetCartesian;
    targetCartesian.x = knownCartesian.x + relativePosition.x;
    targetCartesian.y = knownCartesian.y + relativePosition.y;
    targetCartesian.z = knownCartesian.z + relativePosition.z;

    // 将目标点的空间直角坐标转换为经纬度
    Coordinates targetPoint = cartesianToGeodetic(targetCartesian);

    // 输出结果
    std::cout << "目标点的经纬度和高程：" << std::endl;
    std::cout << "纬度: " << targetPoint.latitude << "°" << std::endl;
    std::cout << "经度: " << targetPoint.longitude << "°" << std::endl;
    std::cout << "高程: " << targetPoint.height << "米" << std::endl;

    return 0;
}
