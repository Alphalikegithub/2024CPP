#include <iostream>
#include <cmath>
#include <iomanip>

// 常量定义
const double a = 6378137.0; // 长半轴
const double f = 1 / 298.257222101; // 扁率
const double b = a * (1 - f); // 短半轴
const double e2 = 2 * f - f * f; // 第一偏心率的平方
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

// 将弧度转换为经纬度
double radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
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
    
    double latRad = atan2(geoCoords.Z + ep2 * b * pow(sinTheta, 3),
                          p - e2 * a * pow(cosTheta, 3));
    double lonRad = atan2(geoCoords.Y, geoCoords.X);
    
    double sinLat = sin(latRad);
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    double h = p / cos(latRad) - N;

    result.lat = radiansToDegrees(latRad);
    result.lon = radiansToDegrees(lonRad);
    result.h = h;
    
    return result;
}

// 将局部坐标转换到地心直角坐标系中
GeocentricCoordinates applyRotationAndTranslation(const GeocentricCoordinates& local, double yaw, const GeocentricCoordinates& origin) {
    double yawRad = degreesToRadians(yaw);

    // 旋转矩阵
    double R[3][3] = {
        {cos(yawRad), -sin(yawRad), 0},
        {sin(yawRad), cos(yawRad), 0},
        {0, 0, 1}
    };

    // 应用旋转矩阵
    double dx_prime = R[0][0] * local.X + R[0][1] * local.Y;
    double dy_prime = R[1][0] * local.X + R[1][1] * local.Y;
    double dz_prime = local.Z; // dz 不变

    // 平移到地心直角坐标系
    GeocentricCoordinates target;
    target.X = origin.X + dx_prime;
    target.Y = origin.Y + dy_prime;
    target.Z = origin.Z + dz_prime;

    return target;
}

int main() {
    // 无人机的经纬度和高程
    GeodeticCoordinates dronePosition = {121.5065, 31.24396, 10.0535};
    double yaw = 0; // 无人机的航向角，单位：度

#if 0
    // 靶板在无人机局部坐标系中的偏移量（假设为右侧下方50厘米）
    GeocentricCoordinates localOffset = {0.5, 0, -0.5}; // x 向右，y 向前，z 向下
    // 将无人机的位置转换为空间直角坐标
    GeocentricCoordinates droneCartesian = geodeticToGeocentric(dronePosition);

    // 计算靶板在地心直角坐标系中的位置
    GeocentricCoordinates targetCartesian = applyRotationAndTranslation(localOffset, yaw, droneCartesian);

    // 将靶板的空间直角坐标转换为经纬度
    GeodeticCoordinates targetPosition = geocentricToGeodetic(targetCartesian);

    // 输出结果
    std::cout << "靶板中心的经纬度和高程：" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "经度: " << targetPosition.lon << "°" << std::endl;
    std::cout << "纬度: " << targetPosition.lat << "°" << std::endl;
    std::cout << "高程: " << targetPosition.h << "米" << std::endl;
#endif

#if 1
GeocentricCoordinates geocentric = geodeticToGeocentric(dronePosition);
    std::cout << "地心笛卡尔空间直角坐标系:" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Geocentric coordinates (X, Y, Z): (" << geocentric.X << ", " << geocentric.Y << ", " << geocentric.Z << ")\n";

    // 示例：地心直角坐标系转换到大地坐标系
    GeodeticCoordinates newGeodetic = geocentricToGeodetic(geocentric);
    std::cout << "大地坐标系(CGCS2000):" << std::endl;
    std::cout << "Geodetic coordinates (Longitude, Latitude, Height): (" << newGeodetic.lon << ", " << newGeodetic.lat << ", " << newGeodetic.h << ")\n";
#endif

    return 0;
}
