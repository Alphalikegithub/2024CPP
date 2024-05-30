#include <iostream>
#include <cmath>
#include <iomanip>

// 椭球参数
const double a = 6378137.0; // 长半轴
const double f = 1 / 298.257222101; // 扁率
const double e2 = 2 * f - f * f; // 第一偏心率的平方
// const double b = a * (1 - f); // 短半轴
const double b = a * sqrt(1 - e2); // 短半轴
const double ep2 = (a * a - b * b) / (b * b); // 第二偏心率的平方

struct Coordinates {
    double latitude;//纬度
    double longitude;//经度
    double height;
};

struct Cartesian {
    double x;
    double y;
    double z;
};

// 将经纬度转换为弧度
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 将经纬度转换为空间直角坐标
Cartesian geodeticToCartesian(const Coordinates& coord) {
    double phi = degreesToRadians(coord.latitude);
    double lambda = degreesToRadians(coord.longitude);
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

    double phi = atan2(cart.z + ep2 * b * pow(sin(theta), 3), p - e2 * a * pow(cos(theta), 3));
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
    //Coordinates knownPoint = {34.0, 108.0, 100.0}; // 例：纬度34度，经度108度，高程100米
    Coordinates knownPoint = {31.24396, 121.5065, 10.0535};
    //Coordinates knownPoint = {纬度,经度,高度}
    // 目标点到已知点的相对距离（假设为500米）和方位角（假设为45度）
    double relativeDistance = 500.0; // 相对距离，单位：米
    double azimuth = 45.0; // 方位角，单位：度

    // 将已知点的经纬度转换为空间直角坐标
    Cartesian knownCartesian = geodeticToCartesian(knownPoint);

    // 根据相对距离和方位角计算目标点的空间直角坐标
    // double phi = knownPoint.latitude * M_PI / 180.0;
    // double lambda = knownPoint.longitude * M_PI / 180.0;
    double phi = degreesToRadians(knownPoint.latitude); // 将纬度转换为弧度
    double lambda = degreesToRadians(knownPoint.longitude); // 将经度转换为弧度
    double h = knownPoint.height;

    // double delta_x = relativeDistance * cos(azimuth * M_PI / 180.0);
    // double delta_y = relativeDistance * sin(azimuth * M_PI / 180.0);

    // double delta_x = relativeDistance * cos(degreesToRadians(azimuth)); // 将方位角转换为弧度
    // double delta_y = relativeDistance * sin(degreesToRadians(azimuth)); // 将方位角转换为弧度

    double delta_x = 0; // 将方位角转换为弧度
    double delta_y = 0; // 将方位角转换为弧度

    Cartesian targetCartesian;
    targetCartesian.x = knownCartesian.x + delta_x;
    targetCartesian.y = knownCartesian.y + delta_y;
    targetCartesian.z = knownCartesian.z;

    //再次打印一下
    std::cout << std::fixed << std::setprecision(10);
    std::cout << knownCartesian.x << std::endl;
    std::cout << knownCartesian.y << std::endl;
    std::cout << knownCartesian.z << std::endl;

    // 将目标点的空间直角坐标转换为经纬度
    Coordinates targetPoint = cartesianToGeodetic(targetCartesian);

    // 输出结果
    std::cout << "目标点的经纬度和高程：" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "纬度: " << targetPoint.latitude << "°" << std::endl;
    std::cout << "经度: " << targetPoint.longitude << "°" << std::endl;
    std::cout << "高程: " << targetPoint.height << "米" << std::endl;

    return 0;
}
