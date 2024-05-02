#include "MyTest.h"
#include "Person.pb.h"


void MyTest::test(){
    //序列化
    Person p;
    p.set_id(10);
    p.set_age(32);
    p.set_sex("man");
    //p.set_name("zhangfei");
    //1.申请内存资源
    p.add_name();
    p.set_name(0,"四郎");
    p.add_name("张麻子");
    p.add_name("师爷");

    p.mutable_addr()->set_addr("东郊镇泰山村安置区");
    p.mutable_addr()->set_num(1705);

    p.set_color(Color::Blue);

     //序列化对象p,最终得到一个字符串
     std::string output;
     p.SerializeToString(&output);

     //反序列化操作
     //再创建一个新的Person对象
     Person pp;
     pp.ParseFromString(output);
     std::cout << "pp.id = " << pp.id() << "," << "pp.sex = " << pp.sex() << "," 
               << "pp.age = " <<pp.age() << "," << std::endl;
     std::cout << "pp.addr ="<< pp.addr().addr() << "," << "pp.addrnum =" << pp.addr().num() << std::endl;
     //先获取动态数组中元素的总个数
     int size = pp.name_size();
     for (int i = 0; i < size; i++)
     {
        std::cout << pp.name(i) << std::endl;
     }
     std::cout << pp.color() << std::endl;

}