#include <iostream>
#include <sstream>
#include <fstream>//文件读写

using std::cout;
using std::endl;
using std::cerr;
using std::ostringstream;
using std::istringstream;
using std::stringstream;
using std::string;
using std::ifstream;

void readConfig(const string &filename);

string int2string(int value){
    ostringstream oss;//中转
    oss << value;
    return oss.str();//获取底层的字符串
}
void test(){
    int numeber  = 10;
    string s1 = int2string(numeber);
    cout << "s1 = " << s1 << endl;
}

void test2(){
    int number1 = 20;
    int number2 = 30;
    stringstream ss ;
    ss << "number1 = " << number1 << ",number2 = " << number2 << endl;
    string s1 = ss.str();
    cout << s1 << endl;

    string key;
    int value;
    while (ss >> key >> value){
        cout << key << "------>" << value << endl;
    }
    cout << key << "------>" << value << endl;
}

void test3(){
    readConfig("my.conf");
}

void readConfig(const string &filename){
    ifstream ifs(filename.c_str());
    /* 
    !ifs等价于!ifs.good()
     */
    if(!ifs){
        cerr << "open " << filename << "error!" << endl;
        return;
    }

    string line;
    while(getline(ifs,line)){
        istringstream iss(line);//初始化
        string key,value;
        iss >> key >> value;

        cout << key << "    " << value << endl;
    }
    ifs.close();
}

int main(int argc,char **argv){
    test3();
    return 0;
}