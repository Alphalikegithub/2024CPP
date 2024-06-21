#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;
using std::endl;

// 常量定义
const double a = 6378137.0; // 长半轴
const double f = 1 / 298.257222101; // 扁率
const double b = a * (1 - f); // 短半轴
const double e2 = 2 * f - f * f; // 第一偏心率的平方
const double ep2 = (a * a - b * b) / (b * b); // 第二偏心率的平方

// 地心笛卡尔空间直角坐标系结构体
struct Cartesian {
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

// 大地坐标系（经度、纬度、高度）到笛卡尔空间直角坐标系（X, Y, Z）的转换
Cartesian geodeticToCartesian(const GeodeticCoordinates &geoCoords) {
    Cartesian result;

    double sinLat = sin(degreesToRadians(geoCoords.lat));
    double cosLat = cos(degreesToRadians(geoCoords.lat));
    double sinLon = sin(degreesToRadians(geoCoords.lon));
    double cosLon = cos(degreesToRadians(geoCoords.lon));
    
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    result.X = (N + geoCoords.h) * cosLat * cosLon;
    result.Y = (N + geoCoords.h) * cosLat * sinLon;
    result.Z = (N * (1 - e2) + geoCoords.h) * sinLat;
    
    return result; // 最后的结果 X, Y, Z 仍然是以米为单位
}

// 笛卡尔空间直角坐标系（X, Y, Z）到大地坐标系（经度、纬度、高度）的转换
GeodeticCoordinates cartesianToGeodetic(const Cartesian &cartCoords) {
    GeodeticCoordinates result;
    double p = sqrt(cartCoords.X * cartCoords.X + cartCoords.Y * cartCoords.Y);
    double theta = atan2(cartCoords.Z * a, p * b);
    
    double sinTheta = sin(theta);
    double cosTheta = cos(theta);
    
    double latRad = atan2(cartCoords.Z + ep2 * b * pow(sinTheta, 3),
                          p - e2 * a * pow(cosTheta, 3));
    double lonRad = atan2(cartCoords.Y, cartCoords.X);
    
    double sinLat = sin(latRad);
    double N = a / sqrt(1 - e2 * sinLat * sinLat);
    double h = p / cos(latRad) - N;

    result.lat = radiansToDegrees(latRad);
    result.lon = radiansToDegrees(lonRad);
    result.h = h;
    
    return result;
}

// 将局部坐标转换到笛卡尔空间直角坐标系中
Cartesian applyRotationAndTranslation(const Cartesian& local, double yaw, const Cartesian& origin) {
    double yawRad = degreesToRadians(yaw);
    cout << "航向角转弧度：" << endl
         << "航向角(转换前) " << yaw
         << "航向角(转换后) " << yawRad;

    // 旋转矩阵（绕Z轴旋转）
    double R[3][3] = {
        {cos(yawRad), -sin(yawRad), 0},
        {sin(yawRad), cos(yawRad), 0},
        {0, 0, 1}
    };

    // 应用旋转矩阵
    double dx_prime = R[0][0] * local.X + R[0][1] * local.Y;
    double dy_prime = R[1][0] * local.X + R[1][1] * local.Y;
    double dz_prime = local.Z; // dz 不变

    cout  << endl;
    cout << "偏移量 : " << endl
              << "dx_prime = " << dx_prime << endl
              << "dy_prime = " << dy_prime << endl
              << "dz_prime = " << dz_prime << endl;

    // 平移到笛卡尔空间直角坐标系
    Cartesian target;
    target.X = origin.X + dx_prime; // 以米为单位
    target.Y = origin.Y + dy_prime;
    target.Z = origin.Z - dz_prime; // 修正为减去高度偏移量

    cout << "坐标偏移后，靶板中心的(X,Y,Z)坐标 : " << endl
              << "(" << target.X << "," << target.Y << "," << target.Z << ")"
              << endl;

    return target;
}

int main() {
    // 无人机的经纬度和高程
    GeodeticCoordinates dronePosition = {110.909850496, 19.575067915, 90.520};
    // GeodeticCoordinates dronePosition = {121.5065, 31.24396, 10.0535};//X: -2852335.3220435134, Y: 4653403.1465222277, Z: 3289053.8582831006
    double yaw = 0; // 无人机的航向角，单位：度
    // double yaw = 34.3;

#if 1
    // 靶板在无人机局部坐标系中的偏移量（假设为前方0厘米，右22.5厘米，下方38厘米）
    Cartesian localOffset = {0, -0.225, 0.38}; // x 向前，y 向右，z 向下
    // 将无人机的位置转换为空间直角坐标
    Cartesian droneCartesian = geodeticToCartesian(dronePosition);

    cout << std::fixed << std::setprecision(10);
    cout << "无人机地心笛卡尔空间直角坐标系:" << endl;
    cout << "X: " << droneCartesian.X << ", Y: " << droneCartesian.Y << ", Z: " << droneCartesian.Z << "\n";

    // 计算靶板在笛卡尔空间直角坐标系中的位置
    Cartesian targetCartesian = applyRotationAndTranslation(localOffset, yaw, droneCartesian);

    cout << "靶板地心笛卡尔空间直角坐标系:" << endl;
    cout << "X: " << targetCartesian.X << ", Y: " << targetCartesian.Y << ", Z: " << targetCartesian.Z << "\n";

    // 将靶板的空间直角坐标转换为经纬度
    GeodeticCoordinates targetPosition = cartesianToGeodetic(targetCartesian);

    // 输出结果
    cout << "靶板中心的经纬度和高程：" << endl;
    cout << std::fixed << std::setprecision(10);
    cout << "经度: " << targetPosition.lon << "°" << endl;
    cout << "纬度: " << targetPosition.lat << "°" << endl;
    cout << "高程: " << targetPosition.h << "米" << endl;
#endif

#if 1
    // 打印地心笛卡尔空间直角坐标系和大地坐标系
    cout << " --------------------------------------------" << endl;
    cout << " ******** 以下是为了便于调试的打印信息 ********" << endl;
    Cartesian cartesian = geodeticToCartesian(dronePosition);
    cout << "地心笛卡尔空间直角坐标系:" << endl;
    cout << std::fixed << std::setprecision(10);
    cout << "Geocentric coordinates (X, Y, Z): (" << cartesian.X << ", " << cartesian.Y << ", " << cartesian.Z << ")\n";

    GeodeticCoordinates newGeodetic = cartesianToGeodetic(cartesian);
    cout << "大地坐标系(CGCS2000):" << endl;
    cout << "Geodetic coordinates (Longitude, Latitude, Height): (" << newGeodetic.lon << ", " << newGeodetic.lat << ", " << newGeodetic.h << ")\n";
#endif

    return 0;
}
