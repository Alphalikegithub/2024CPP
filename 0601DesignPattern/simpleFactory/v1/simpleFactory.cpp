#include <iostream>

using namespace std;

class AbstractSmile{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {};//虚析构函数
};

class SheepSmile : public AbstractSmile{
public:
    void transform() override{
        cout << "变成人兽 -- 山羊人形态" << endl;
    }
    void ability() override{
        cout << "将手臂变成绵羊角的招式 -- 巨羊角" << endl;
    }
};

class LionSmile : public AbstractSmile{
public:
    void transform() override{
        cout << "变成人兽 -- 狮子人形态..." << endl;
    }
    void ability() override{
        cout << "火遁 豪火球之术..." << endl;
    }
};

class BatSmile : public AbstractSmile{
public:
    void transform() override{
        cout << "变成人兽 -- 蝙蝠人形态..." << endl;
    }
    void ability() override{
        cout << "声纳引箭之万剑归宗..." << endl;
    }
};

enum class Type:char{Sheep,Lion,Bat};//通过:来连接数据类型
//定义工厂类
class SmileFactory{
public:
    //让父类指针指向子类对象(多态)
    AbstractSmile* createSmile(Type type){
        AbstractSmile* ptr = nullptr;
        switch (type)
        {
        case Type::Sheep:   
            /* code */    
            ptr = new SheepSmile;
            break;
        case Type::Lion:
            ptr = new LionSmile;
            break;
        case Type::Bat:
            ptr = new BatSmile;
            break;
        default:
            break;
        }
        return ptr;
    }

};
int main(int argc,char** agrv){
    //创建一个工厂类的对象
    SmileFactory* factory = new SmileFactory;
    //需要让父类指针指向子类对象
    AbstractSmile* obj = factory->createSmile(Type::Lion);
    obj->transform();
    obj->ability();
    return 0;
}