#include <iostream>
#include <string>
using  std::string;
// tookCowboy_Cow("matchmaker","river");
//     stoleWeaver_spinningWheel("matchmaker","cow");
//     searchCow("cowboy");
//     searchSpinningWheel("weaver");
//     meet("cowboy","weaver");
//     married("cowboy","weaver");

class Matchmaker{
public:
    void dosomething(string cow,string spinningWheel);
    void seekHelp(string name);//求助：找牛郎借牛，找织女借纺车

};

class Cowboy{
public:
    void searchCow();
    void meeting(string name);
    void getMarried(string name);
    string getName();
    string getCow();
private:
    string m_cow;
};

class Weaver{
public:
    void searchSpinningWheel();
    void meeting(string name);
    void getMarried(string name);
    string getName();
    string getSpinningWheel();
private:
    string m_SpinningWheel;
};

int main(int argc,char** argv){
    Matchmaker* matchmaker = new Matchmaker;
    Cowboy* cowboy = new Cowboy;
    Weaver* weaver = new Weaver;

    string cow = cowboy->getCow();
    string spinningWheel = weaver->getSpinningWheel();

    matchmaker->dosomething(cow,spinningWheel);
    matchmaker->seekHelp(cowboy->getName());
    matchmaker->seekHelp(weaver->getName());

    cowboy->searchCow();
    weaver->searchSpinningWheel();

    cowboy->meeting(weaver->getName());
    weaver->meeting(cowboy->getName());

    cowboy->getMarried(weaver->getName());
    weaver->getMarried(cowboy->getName());

    return 0;
}