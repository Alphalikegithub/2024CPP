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
//如果要增加新的恶魔果实（数据类型），不仅仅要修改enum中的枚举类型，下方switch case中条件判断也会成倍增长，违反了开放封闭原则
//定义工厂类
class AbstractFactory{
public:
    //让父类指针指向子类对象(多态)
    virtual AbstractSmile* createSmile() = 0;//纯虚函数
    virtual ~AbstractFactory(){}
};

//生产山羊的恶魔果实
class SheepFacory : public AbstractFactory
{
public:
    AbstractSmile* createSmile(){
        return new SheepSmile;
    }
    ~SheepFacory(){
        cout << "SheepFacory 被析构了..." << endl;
    }
};
//生产狮子的恶魔果实
class LionFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile(){
        return new LionSmile;
    }
    ~LionFactory(){
        cout << "LionFactory 被析构了..." << endl;
    }
};
//生产蝙蝠的恶魔果实
class BatFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile(){
        return new BatSmile;
    }
    ~BatFactory(){
        cout << "BatFactory 被析构了..." << endl;
    }
};
int main(int argc,char** agrv){
    //创建一个工厂类的对象
    AbstractFactory* factory = new SheepFacory;
    // AbstractFactory* factory = new LionFactory;
    // AbstractFactory* factory = new BatFactory;
    //需要让父类指针指向子类对象
    AbstractSmile* obj = factory->createSmile();
    obj->transform();
    obj->ability();

    delete obj;
    delete factory;//虽然delete的是父类指针，但是父类指针指向的是子类对象，所以析构的是子类对象中的资源
    return 0;
}