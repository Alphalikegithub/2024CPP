#include <iostream>
#include <cmath>
#include <array>
#include <iomanip>



class latlon
{
private:
    /* data */
public:
    latlon(/* args */);
    ~latlon();

public:
    std::array<double, 3> LongLatOffset(double lon, double lat, double a, double dst,double height);
        // double[] LongLatOffset(double lon, double lat, double a, double dst)
        // {
        //     double arc = 6371.393 * 1000;
        //     lat += dst * Math.Cos(a) / (arc * 2 * Math.PI / 360);
		// 	lon += dst * Math.Sin(a) / (arc * Math.Cos(lat * Math.PI /	180) * 2 * Math.PI / 360);
        //     return new[] { lon, lat };
        // }
};

latlon::latlon(/* args */)
{
}

latlon::~latlon()
{
}

std::array<double, 3> latlon::LongLatOffset(double lon, double lat, double degrees, double dst ,double height)
{
    // 弧度 = 角度 * (π / 180)  
    double radians = (270 + degrees) * (M_PI / 180.0); 
    double arc = 6371.393 * 1000; // 地球半径，单位为米
    lat += dst * std::cos(radians) / (arc * 2 * M_PI / 360);
    lon += dst * std::sin(radians) / (arc * std::cos(lat * M_PI / 180) * 2 * M_PI / 360);
    height -= 0.38;
    return { lon, lat ,height };
}
int main() {
    latlon ll;
    double lon = 110.909850496;
    double lat = 19.575067915;
    //double a = M_PI / 4; // 45度角
    double height = 90.520;

    double degrees = 34.3;  
    // double degrees = 0; 


    double num1 = 22.5;  // 单位: 厘米
    double num2 = 38.0;  // 单位: 厘米
    // 计算平方和  
    double sumOfSquares = std::pow(num1, 2) + std::pow(num2, 2);  
    // 计算平方和的平方根  
    double dst = std::sqrt(sumOfSquares);  
    // double dst = sqrt(22.5 * 22.5 + 38 * 38); // 44.16163493厘米
    // 将距离转换为米
    dst /= 100;
    
    std::array<double, 3> result = ll.LongLatOffset(lon, lat, degrees, dst, height);
    std::cout << std::fixed << std::setprecision(14);
    // std::cout << "开平方" << dst << std::endl;
    // std::cout << std::endl << std::endl << std::endl;
    std::cout << std::endl;
    std::cout << "新经度: " << result[0] << std::endl 
              << "新纬度: " << result[1] << std::endl 
              << "新高度: " << result[2]  << std::endl;

    
    return 0;
}