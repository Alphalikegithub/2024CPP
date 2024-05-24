#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
// tookCowboy_Cow("matchmaker","river");
//     stoleWeaver_spinningWheel("matchmaker","cow");
//     searchCow("cowboy");
//     searchSpinningWheel("weaver");
//     meet("cowboy","weaver");
//     married("cowboy","weaver");
class Person{
public:
    void meeting(Person* person){
        //cout << "遇见了" << name << endl;
        //相互见面
        if(m_person == nullptr){
            m_person = person;
            person->meeting(this);
        }
    }
    void getMarried(){
        if(m_flag){
            m_flag = false;
            marry();
            m_person->getMarried();
        }
        //cout << "过上了没羞没臊的生活!" << endl;
    }
    virtual string getName() = 0;
    virtual void search() = 0;
    virtual string getProperty() = 0;
    virtual void marry() = 0;
protected:
    Person* m_person = nullptr;
    bool m_flag = true;
};



class Cowboy : public Person{
public:
    string getName() override
    {
        string cowboy_name = "牛郎";
        return cowboy_name;
    }

    void search() override
    {
        cout << "我的牛丢了，我去找牛..." << endl;
    }
    
    string getProperty() override
    {
        return m_cow;
    }

    void marry() override
    {
        cout << "🙏织女能看上我..." << endl;
    }
private:
    string m_cow = "五彩神牛";
};

class Weaver : public Person{
public:
    string getName() override
    {
        string weaver_name = "织女";
        return weaver_name;
    }

    void search() override
    {
        cout << "我的纺车丢了，我去找纺车..." << endl;
    }
    // void meeting(string name);
    // void getMarried(string name);
    
    string getProperty() override
    {
        return m_SpinningWheel;
    }

    void marry() override
    {
        cout << "未来可期" << endl;
    }
private:
    string m_SpinningWheel = "七彩仙女";
};

class Matchmaker{
public:
    Matchmaker(Cowboy* cowboy,Weaver* weaver)
    :m_cowboy(cowboy),m_weaver(weaver){

    }
    void dosomething(){
        cout << "柳树精偷偷牵走了牛郎的牛，将其栓在河边吃草" << m_cowboy->getProperty() << endl;
        cout << "柳树精偷偷偷走了织女的纺车，将其放到了牛郎的牛车上" << m_weaver->getProperty() << endl;
    }
    //求助：找牛郎借牛，找织女借纺车
    void seekHelp(){
        m_cowboy->search();
        m_weaver->search();
    }
private:
    Cowboy* m_cowboy = nullptr;
    Weaver* m_weaver = nullptr;
};

int main(int argc,char** argv){
    Cowboy* cowboy = new Cowboy;
    Weaver* weaver = new Weaver;
    Matchmaker* matchmaker = new Matchmaker(cowboy,weaver);

    matchmaker->dosomething();
    matchmaker->seekHelp();

    cowboy->meeting(weaver);
    weaver->meeting(cowboy);

    cowboy->getMarried();
    weaver->getMarried();

    return 0;
}

//子类重写父类的虚函数
//父类的指针或者引用指向子类对象
//子类对象调用子类内部重写的虚函数(从父类继承过来的)
//动态绑定是在运行的时候确定指针指向的对象是谁
/* 一个抽象类 不能为该类创建实例化对象 */