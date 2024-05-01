#include "MyTest.h"
#include "Person.pb.h"

void MyTest::test(){
    //序列化
    Person p;
    p.set_id(10);
    p.set_age(32);
    p.set_sex("man");
    p.set_name("zhangfei");

     //序列化对象p,最终得到一个字符串
     std::string output;
     p.SerializeToString(&output);

     //反序列化操作
     //再创建一个新的Person对象
     Person pp;
     pp.ParseFromString(output);
     std::cout << "pp.id = " << pp.id() << "," << "pp.sex = " << pp.sex() << "," << "pp.age = " <<pp.age() << "," << "pp.name = " <<pp.name() << std::endl;

}