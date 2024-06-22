#include <iostream>

using namespace std;

//船体
class ShipBody
{
public:
    virtual string getBody() = 0;
    virtual ~ShipBody(){}//为什么给基类添加虚析构函数？用基类指针指向子类对象，以便析构子类对象中的资源
};
//木质船体
class WoodBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("使用《木材》制作海贼船的船体...");
    }
};

//木质船体
class IronBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("使用《钢铁》制作海贼船的船体...");
    }
};

//合成金属船体
class MetalBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("使用《合金》制作海贼船的船体...");
    }
};

//引擎
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine(){}//为什么给基类添加虚析构函数？用基类指针指向子类对象，以便析构子类对象中的资源
};

class Human : public Engine
{
public :
    string getEngine() override
    {
        return "海贼船的动力方式是《手动划桨》...";
    }
};

class Diesel : public Engine
{
public :
    string getEngine() override
    {
        return "海贼船的动力方式是《内燃机》...";
    }
};

class Nuclear : public Engine
{
public :
    string getEngine() override
    {
        return "海贼船的动力方式是《核反应堆》...";
    }
};

//武器
class Weapons
{
public:
    virtual string getWeapons() = 0;
    virtual ~Weapons(){}//为什么给基类添加虚析构函数？用基类指针指向子类对象，以便析构子类对象中的资源
};

class Gun : public Weapons
{
public:
    string getWeapons() override{
        return string("船上的武器系统是<枪支>...");
    }
};

class Cannon : public Weapons
{
public:
    string getWeapons() override{
        return string("船上的武器系统是<加农炮>...");
    }
};

class Laser : public Weapons
{
public:
    string getWeapons() override{
        return string("船上的武器系统是<激光>...");
    }
};

//定义一个完整的船的类
class Ship
{
public:
    Ship(ShipBody* body,Engine* engine,Weapons* weapons)
    :m_body(body)
    ,m_engine(engine)
    ,m_weapons(weapons)
    {

    }

    ~Ship( ){
        delete m_body;
        delete m_engine;
        delete m_weapons;
    }

    string getProperty(){
        string info = m_body->getBody() + m_engine->getEngine() + m_weapons->getWeapons();
        return info;
    }
private:
    /* data */
    ShipBody* m_body;
    Engine* m_engine;
    Weapons* m_weapons;
};

//工厂类-抽象
class AbstractFactory
{

public:
    virtual Ship* createShip() = 0;
    virtual ~AbstractFactory() {}
};

class BasicFactory : public AbstractFactory
{
public:
    Ship* createShip() override{
        Ship* ship = new Ship(new WoodBody,new Human,new Gun);
        cout << "<基础性的海贼船>已经建造完毕!!!" << endl;
        return  ship;
    }
};

class StandardFactory : public AbstractFactory
{
public:
    Ship* createShip() override{
        Ship* ship = new Ship(new IronBody,new Diesel,new Cannon);
        cout << "<标准性的海贼船>已经建造完毕!!!" << endl;
        return  ship;
    }
};

class ultimateFactory : public AbstractFactory
{
public:
    Ship* createShip() override{
        Ship* ship = new Ship(new MetalBody,new Nuclear,new Laser);
        cout << "<旗舰性的海贼船>已经建造完毕!!!" << endl;
        return  ship;
    }
};

int main(int argc,char** agrv){
    //建造旗舰型的海贼船
    AbstractFactory* factory = new ultimateFactory;
    Ship* ship = factory->createShip();
    string msg = ship->getProperty();
    cout << msg << endl;
    delete ship;
    delete factory;
    return 0;
    
}