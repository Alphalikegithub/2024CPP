#include <iostream>
#include <cmath>
#include <iomanip>

// 常量定义
// const double a = 6378137.0; // 长轴
// const double f = 1.0 / 298.257222101; // 扁率
// const double b = a * (1 - f); // 短轴
// const double e2 = 1 - (b * b) / (a * a); // 第一偏心率的平方

const double a = 6378137.0; // 长半轴
const double f = 1 / 298.257222101; // 扁率
const double e2 = 2 * f - f * f; // 第一偏心率的平方
const double b = a * (1 - f); // 短半轴
//const double b = a * sqrt(1 - e2); // 短半轴

const double ep2 = (a * a - b * b) / (b * b); // 第二偏心率的平方

// 地心直角坐标系结构体
struct GeocentricCoordinates {
    double X;
    double Y;
    double Z;
};

// 大地坐标系结构体
struct GeodeticCoordinates {
    double lon; // 经度
    double lat; // 纬度
    double h;   // 高度
};

// 将经纬度转换为弧度
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 大地坐标系（经度、纬度、高度）到地心直角坐标系（X, Y, Z）的转换
GeocentricCoordinates geodeticToGeocentric(const GeodeticCoordinates &geoCoords) {
    GeocentricCoordinates result;

    double sinLat = sin(degreesToRadians(geoCoords.lat));
    double cosLat = cos(degreesToRadians(geoCoords.lat));
    double sinLon = sin(degreesToRadians(geoCoords.lon));
    double cosLon = cos(degreesToRadians(geoCoords.lon));
    
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    result.X = (N + geoCoords.h) * cosLat * cosLon;
    result.Y = (N + geoCoords.h) * cosLat * sinLon;
    result.Z = (N * (1 - e2) + geoCoords.h) * sinLat;
    
    return result;
}

// 地心直角坐标系（X, Y, Z）到大地坐标系（经度、纬度、高度）的转换
GeodeticCoordinates geocentricToGeodetic(const GeocentricCoordinates &geoCoords) {
    GeodeticCoordinates result;
    double p = sqrt(geoCoords.X * geoCoords.X + geoCoords.Y * geoCoords.Y);
    double theta = atan2(geoCoords.Z * a, p * b);
    
    double sinTheta = sin(theta);
    double cosTheta = cos(theta);
    
    //计算的是目标点的纬度，它使用了椭球体参数中的第二偏心率的平方 𝑒′^ 2
    result.lat = atan2(geoCoords.Z + ep2 * b * pow(sinTheta,3),
                       p - e2 * a * pow(cosTheta,3)) * 180.0 / M_PI;
    result.lon = atan2(geoCoords.Y, geoCoords.X) * 180.0 / M_PI;
    
    double sinLat = sin(degreesToRadians(result.lat));
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    result.h = p / cos(degreesToRadians(result.lat)) - N;
    
    return result;
}

int main() {
    // 示例：大地坐标系转换到地心直角坐标系
    GeodeticCoordinates geodetic = {121.5065, 31.24396, 10.0535}; // 经度、纬度、高度

    GeocentricCoordinates geocentric = geodeticToGeocentric(geodetic);
    std::cout << "地心笛卡尔空间直角坐标系:" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Geocentric coordinates (X, Y, Z): (" << geocentric.X << ", " << geocentric.Y << ", " << geocentric.Z << ")\n";

    // 示例：地心直角坐标系转换到大地坐标系
    GeodeticCoordinates newGeodetic = geocentricToGeodetic(geocentric);
    std::cout << "大地坐标系(CGCS2000):" << std::endl;
    std::cout << "Geodetic coordinates (Longitude, Latitude, Height): (" << newGeodetic.lon << ", " << newGeodetic.lat << ", " << newGeodetic.h << ")\n";

    return 0;
}
