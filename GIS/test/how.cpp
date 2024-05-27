#include <iostream>
#include <cmath>

// 椭球参数
const double a = 6378137.0; // 长半轴
const double f = 1 / 298.257223563; // 扁率
const double e2 = 2 * f - f * f; // 第一偏心率的平方
const double b = a * sqrt(1 - e2); // 短半轴

// 将角度转换为弧度
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 将弧度转换为度
double toDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

// 将经纬度转换为直角坐标系
struct CartesianPoint {
    double x;
    double y;
    double z;
};

// 将直角坐标转换为经纬度和高程
struct GeographicPoint {
    double lon;
    double lat;
    double alt;
};

// 将经纬度转换为直角坐标系
CartesianPoint geographicToCartesian(const GeographicPoint& point) {
    double lon_rad = toRadians(point.lon);
    double lat_rad = toRadians(point.lat);
    double sin_latitude = sin(lat_rad);
    double N = a / sqrt(1 - e2 * sin_latitude * sin_latitude);
    CartesianPoint cartesian;
    cartesian.x = (N + point.alt) * cos(lat_rad) * cos(lon_rad);
    cartesian.y = (N + point.alt) * cos(lat_rad) * sin(lon_rad);
    cartesian.z = ((1 - e2) * N + point.alt) * sin(lat_rad);
    return cartesian;
}

// 将直角坐标转换为经纬度和高程
GeographicPoint cartesianToGeographic(const CartesianPoint& point) {
    double p = sqrt(point.x * point.x + point.y * point.y);
    double theta = atan2(point.z * a, p * b);

    double lon = atan2(point.y, point.x);
    double lat = atan2(point.z + e2 * b * pow(sin(theta), 3), p - e2 * a * pow(cos(theta), 3));
    double N = a / sqrt(1 - e2 * sin(lat) * sin(lat));
    double alt = p / cos(lat) - N;

    return {toDegrees(lon), toDegrees(lat), alt};
}

int main() {
    // 起始点的经纬度和高程
    GeographicPoint startPoint = {34.0, 108.0, 100.0}; // 例：纬度34度，经度108度，高程100米

    // 相对距离和方位角
    double distance = 500.0;   // 例如，500米
    double azimuth = toRadians(45.0);  // 例如，45度

    // 将起始点的经纬度转换为直角坐标系
    CartesianPoint startPointCartesian = geographicToCartesian(startPoint);

    // 输出起始点的直角坐标
    std::cout << "起始点的直角坐标：" << std::endl;
    std::cout << "X: " << startPointCartesian.x << std::endl;
    std::cout << "Y: " << startPointCartesian.y << std::endl;
    std::cout << "Z: " << startPointCartesian.z << std::endl;

    // 计算目标点的直角坐标
    CartesianPoint targetCartesian;
    targetCartesian.x = startPointCartesian.x + distance * cos(azimuth);
    targetCartesian.y = startPointCartesian.y + distance * sin(azimuth);
    targetCartesian.z = startPointCartesian.z;

    // 输出目标点的直角坐标
    std::cout << "目标点的直角坐标：" << std::endl;
    std::cout << "X: " << targetCartesian.x << std::endl;
    std::cout << "Y: " << targetCartesian.y << std::endl;
    std::cout << "Z: " << targetCartesian.z << std::endl;

    // 将目标点的直角坐标转换为经纬度和高程
    GeographicPoint endPoint = cartesianToGeographic(targetCartesian);

    // 输出目标点的经纬度和高程
    std::cout << "目标点的经度: " << endPoint.lon << std::endl;
    std::cout << "目标点的纬度: " << endPoint.lat << std::endl;
    std::cout << "目标点的高程: " << endPoint.alt << std::endl;

    return 0;
}
