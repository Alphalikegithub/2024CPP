#include <iostream>
#include <cmath>
#include <array>

class latlon
{
private:
    /* data */
public:
    latlon(/* args */);
    ~latlon();

    // <summary>
        /// 计算移动后的经纬度
        /// </summary>
        /// <param name="lon">经度</param>
        /// <param name="lat">纬度</param>
        /// <param name="a">方位角（弧度）</param>
        /// <param name="dst">移动距离</param>
        /// <returns></returns>
public:
    std::array<double, 2> LongLatOffset(double lon, double lat, double a, double dst);
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

std::array<double, 2> latlon::LongLatOffset(double lon, double lat, double a, double dst)
{
    double arc = 6371.393 * 1000; // 地球半径，单位为米
    lat += dst * std::cos(a) / (arc * 2 * M_PI / 360);
    lon += dst * std::sin(a) / (arc * std::cos(lat * M_PI / 180) * 2 * M_PI / 360);
    return { lon, lat };
}
int main() {
    latlon ll;
    double lon = 100.0;
    double lat = 20.0;
    double a = M_PI / 4; // 45度角
    double dst = 1000.0; // 1000米

    std::array<double, 2> result = ll.LongLatOffset(lon, lat, a, dst);
    std::cout << "新经度: " << result[0] << ", 新纬度: " << result[1] << std::endl;

    return 0;
}