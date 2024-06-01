#include <iostream>
#include <cmath>
#include <iomanip>

// 常量定义
const double a = 6378137.0; // 长轴
const double f = 1.0 / 298.257222101; // 扁率
const double b = a * (1 - f); // 短轴
const double e2 = 1 - (b * b) / (a * a); // 第一偏心率的平方
const double ep2 = (a * a - b * b) / (b * b); // 第二偏心率的平方

// 大地坐标系（经度、纬度、高度）到地心直角坐标系（X, Y, Z）的转换
void geodeticToGeocentric(double lon, double lat, double h, double &X, double &Y, double &Z) {
    double sinLat = sin(lat * M_PI / 180.0);
    double cosLat = cos(lat * M_PI / 180.0);
    double sinLon = sin(lon * M_PI / 180.0);
    double cosLon = cos(lon * M_PI / 180.0);
    
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    X = (N + h) * cosLat * cosLon;
    Y = (N + h) * cosLat * sinLon;
    Z = (N * (1 - e2) + h) * sinLat;
}

// 地心直角坐标系（X, Y, Z）到大地坐标系（经度、纬度、高度）的转换
void geocentricToGeodetic(double X, double Y, double Z, double &lon, double &lat, double &h) {
    double p = sqrt(X * X + Y * Y);
    double theta = atan2(Z * a, p * b);
    
    double sinTheta = sin(theta);
    double cosTheta = cos(theta);
    
    lat = atan2(Z + ep2 * b * sinTheta * sinTheta * sinTheta,
                p - e2 * a * cosTheta * cosTheta * cosTheta) * 180.0 / M_PI;
    lon = atan2(Y, X) * 180.0 / M_PI;
    
    double sinLat = sin(lat * M_PI / 180.0);
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    h = p / cos(lat * M_PI / 180.0) - N;
}

int main() {
    // 示例：大地坐标系转换到地心直角坐标系
    double lon = 121.5065; // 经度
    double lat = 31.24396; // 纬度
    double h = 10.0535; // 高度

    double X, Y, Z;
    geodeticToGeocentric(lon, lat, h, X, Y, Z);
    std::cout << "地心笛卡尔空间直角坐标系:" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Geocentric coordinates (X, Y, Z): (" << X << ", " << Y << ", " << Z << ")\n";

    // 示例：地心直角坐标系转换到大地坐标系
    double newLon, newLat, newH;
    geocentricToGeodetic(X, Y, Z, newLon, newLat, newH);
    std::cout << "大地坐标系(CGCS2000):" << std::endl;
    std::cout << "Geodetic coordinates (Longitude, Latitude, Height): (" << newLon << ", " << newLat << ", " << newH << ")\n";

    return 0;
}
