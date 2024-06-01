#include <iostream>
#include <cmath>

// 定义椭球体参数
const double a = 6378137.0;  // 地球的赤道半径，单位：米
const double f = 1 / 298.257223563;  // 地球扁率的倒数

// 将角度转换为弧度
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
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
    double e2 = 2 * f - f * f;
    double N = a / sqrt(1 - e2 * sin_latitude * sin_latitude);
    CartesianPoint cartesian;
    cartesian.x = (N + point.alt) * cos(lat_rad) * cos(lon_rad);
    cartesian.y = (N + point.alt) * cos(lat_rad) * sin(lon_rad);
    //cartesian.z = ((1 - f * f) * N + point.alt) * sin(lat_rad);
    cartesian.z = ((1 - e2) * N + point.alt) * sin(lat_rad);
    return cartesian;
}

// 将直角坐标转换为经纬度和高程
GeographicPoint cartesianToGeographic(const CartesianPoint& point) {
    //计算椭球体的第一偏心率的平方 e2。
    double e2 = 2 * f - f * f;
    // 短半轴
    double b = a * sqrt(1 - e2);
    double p = sqrt(point.x * point.x + point.y * point.y);
    double theta = atan2(point.z * a, p * b);

    //计算直角坐标系点 (x, y, z) 到原点的距离 rho，即立体直角坐标系中点 (x, y, z) 到原点 (0, 0, 0) 的距离。
    double rho = sqrt(point.x * point.x + point.y * point.y);
    //计算经度 lon，即直角坐标系点 (x, y) 对应的极坐标系中的角度，使用 atan2 函数可以保证得到的角度在正确的象限
    double lon = atan2(point.y, point.x);

    

    //计算纬度 lat，即直角坐标系点 (x, y, z) 对应的球面坐标系中的角度，这里使用了反正切函数 atan2(point.z, rho)。
    // double lat = atan2(point.z, rho);
    double lat = atan2(point.z + e2 * b * pow(sin(theta), 3), p - e2 * a * pow(cos(theta), 3));
    //计算纬度对应的正弦值 sin_latitude。
    double sin_latitude = sin(lat);

    //根据纬度和椭球体的参数计算卯酉圈曲率半径 N。
    double N = a / sqrt(1 - e2 * sin_latitude * sin_latitude);
    //计算高程 alt，即直角坐标系点 (x, y, z) 到椭球体表面的垂直距离。
    double alt = rho / cos(lat) - N;
    return {lon * 180 / M_PI, lat * 180 / M_PI, alt};
}

int main() {
    // 起始点的经纬度和高程
    GeographicPoint startPoint;
    // startPoint.lon = 116.4074;  // 例如，北京的经度
    // startPoint.lat = 39.9042;   // 例如，北京的纬度
    // startPoint.alt = 50.0;      // 例如，北京的高程

    startPoint.lon = 108.0;  // 例如，北京的经度
    startPoint.lat = 34.0;   // 例如，北京的纬度
    startPoint.alt = 100.0;      // 例如，北京的高程
    // 相对距离和方位角
    double distance = 500.0;   // 例如，100公里
    double azimuth = toRadians(45.0);  // 例如，45度

    // 将起始点的经纬度转换为直角坐标系
    CartesianPoint startPointCartesian = geographicToCartesian(startPoint);

    // 计算目标点的直角坐标
    CartesianPoint targetCartesian;
    targetCartesian.x = startPointCartesian.x + distance * cos(azimuth);
    targetCartesian.y = startPointCartesian.y + distance * sin(azimuth);
    targetCartesian.z = startPointCartesian.z;  // 假设高程没有变化

    // 将目标点的直角坐标转换为经纬度和高程
    GeographicPoint endPoint = cartesianToGeographic(targetCartesian);

    // 输出目标点的经纬度和高程
    std::cout << "目标点的经度: " << endPoint.lon << std::endl;
    std::cout << "目标点的纬度: " << endPoint.lat << std::endl;
    std::cout << "目标点的高程: " << endPoint.alt << std::endl;

    return 0;
}