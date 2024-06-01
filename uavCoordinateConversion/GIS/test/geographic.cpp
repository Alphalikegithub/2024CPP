#include <iostream>
#include <cmath>

// 定义椭球体参数
const double a = 6378137.0;  // 地球的赤道半径，单位：米
const double f = 1 / 298.257223563;  // 地球扁率的倒数

// 定义结构体表示Cartesian坐标系的点
struct CartesianPoint {
    double x;
    double y;
    double z;
};

// 定义结构体表示Geographic坐标系的点
struct GeographicPoint {
    double lon;
    double lat;
    double alt;
};

// 将角度转换为弧度
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 将经纬度转换为直角坐标系
CartesianPoint geographicToCartesian(const GeographicPoint& point) {
    double lon_rad = toRadians(point.lon);
    double lat_rad = toRadians(point.lat);
    double sin_latitude = sin(lat_rad);
    double e2 = 2 * f - f * f;
    double N = a / sqrt(1 - e2 * sin_latitude * sin_latitude);
    CartesianPoint cartesian;
    cartesian.x = (N + point.alt) * cos(lat_rad) * cos(lon_rad);
    cartesian.y = (N + point.alt) * cos(lat_rad) * sin(lon_rad);
    cartesian.z = (N * (1 - e2) + point.alt) * sin(lat_rad); // 使用计算 N 的公式
    return cartesian;
}

// 将直角坐标转换为经纬度和高程
GeographicPoint cartesianToGeographic(const CartesianPoint& point) {
    double longitude_rad = atan2(point.y, point.x);
    double latitude_rad = atan2(point.z, sqrt(point.x * point.x + point.y * point.y));
    double sin_latitude = sin(latitude_rad);
    double e2 = 2 * f - f * f;
    double N = a / sqrt(1 - e2 * sin_latitude * sin_latitude);
    GeographicPoint geographic;
    geographic.alt = sqrt(point.x * point.x + point.y * point.y + point.z * point.z) - N * (1 - e2);
    geographic.lat = latitude_rad * 180 / M_PI;
    geographic.lon = longitude_rad * 180 / M_PI;
    return geographic;
}

int main() {
    // 起始点的经纬度和高程
    GeographicPoint startPoint;
    startPoint.lon = 116.4074;  // 例如，北京的经度
    startPoint.lat = 39.9042;   // 例如，北京的纬度
    startPoint.alt = 50.0;      // 例如，北京的高程

    // 将经纬度转换为直角坐标系
    CartesianPoint cartesianPoint = geographicToCartesian(startPoint);

    // 将直角坐标转换为经纬度和高程
    GeographicPoint endPoint = cartesianToGeographic(cartesianPoint);

    // 输出目标点的经纬度和高程
    std::cout << "目标点的经度: " << endPoint.lon << std::endl;
    std::cout << "目标点的纬度: " << endPoint.lat << std::endl;
    std::cout << "目标点的高程: " << endPoint.alt << std::endl;

    return 0;
}
