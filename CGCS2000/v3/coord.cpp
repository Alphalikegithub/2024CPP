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

// 将局部坐标转换到地心笛卡尔坐标系中
Cartesian applyRotationAndTranslation(const Cartesian& local, double yaw, const Cartesian& origin) {
    double yaw_rad = degreesToRadians(yaw);

    // 旋转矩阵
    double R[3][3] = {
        {cos(yaw_rad), -sin(yaw_rad), 0},
        {sin(yaw_rad), cos(yaw_rad), 0},
        {0, 0, 1}
    };

    // 应用旋转矩阵
    double dx_prime = R[0][0] * local.x + R[0][1] * local.y;
    double dy_prime = R[1][0] * local.x + R[1][1] * local.y;
    double dz_prime = local.z; // dz 不变

    // 平移到地心笛卡尔坐标系
    Cartesian target;
    target.x = origin.x + dx_prime;
    target.y = origin.y + dy_prime;
    target.z = origin.z + dz_prime;

    return target;
}

int main() {
    // 无人机的经纬度和高程
    Coordinates dronePosition = {31.24396, 121.5065, 10.0535};
    double yaw = 45.0; // 无人机的航向角，单位：度

    // 靶板在无人机局部坐标系中的偏移量（假设为右侧下方50厘米）
    Cartesian localOffset = {0.5, 0, -0.5}; // x 向右，y 向前，z 向下

    // 将无人机的位置转换为空间直角坐标
    Cartesian droneCartesian = geodeticToCartesian(dronePosition);

    // 计算靶板在地心笛卡尔坐标系中的位置
    Cartesian targetCartesian = applyRotationAndTranslation(localOffset, yaw, droneCartesian);

    // 将靶板的空间直角坐标转换为经纬度
    Coordinates targetPosition = cartesianToGeodetic(targetCartesian);

    // 输出结果
    std::cout << "靶板中心的经纬度和高程：" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "纬度: " << targetPosition.latitude << "°" << std::endl;
    std::cout << "经度: " << targetPosition.longitude << "°" << std::endl;
    std::cout << "高程: " << targetPosition.height << "米" << std::endl;

    return 0;
}
