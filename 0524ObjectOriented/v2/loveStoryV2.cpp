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
    void meeting(string name){
        cout << "遇见了" << name << endl;
    }
    void getMarried(){
        cout << "过上了没羞没臊的生活!" << endl;
    }

};



class Cowboy : public Person{
public:
    void searchCow(){
        cout << "牛郎去找牛了..." << endl;
    }
    // void meeting(string name);
    // void getMarried(string name);
    string getName(){
        string cowboy_name = "牛郎";
        return cowboy_name;
    }
    string getCow(){
        return m_cow;
    }
private:
    string m_cow;
};

class Weaver : public Person{
public:
    void searchSpinningWheel(){
        cout << "织女去找纺车了..." << endl;
    }
    // void meeting(string name);
    // void getMarried(string name);
    string getName(){
        string weaver_name = "织女";
        return weaver_name;
    }
    string getSpinningWheel(){
        return m_SpinningWheel;
    }
private:
    string m_SpinningWheel;
};

class Matchmaker{
public:
    Matchmaker(Cowboy* cowboy,Weaver* weaver)
    :m_cowboy(cowboy),m_weaver(weaver){

    }
    void dosomething(){
        cout << "柳树精偷偷牵走了牛郎的牛，将其栓在河边吃草" << m_cowboy->getCow() << endl;
        cout << "柳树精偷偷偷走了织女的纺车，将其放到了牛郎的牛车上" << m_weaver->getSpinningWheel() << endl;
    }
    //求助：找牛郎借牛，找织女借纺车
    void seekHelp(){
        m_cowboy->searchCow();
        m_weaver->searchSpinningWheel();
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

    cowboy->meeting(weaver->getName());
    weaver->meeting(cowboy->getName());

    cowboy->getMarried();
    weaver->getMarried();

    return 0;
}

