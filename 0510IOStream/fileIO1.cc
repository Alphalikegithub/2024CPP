#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
using std::string;

void test(){
    ifstream ifs("test.txt");//打开一个名为test.txt的文件
    if(!ifs.good()){
        cerr << "ifstream is not good" << endl;
        return;
    }
    //通过文件流去读取文件
    /*  */
    //对于文件输入流而言，默认以空格为分隔符
    string line;
    while(ifs >> line){
        cout << line << endl;
    }
    ifs.close();
}

int main(int argc,char **aggv){
    test();
    return 0;
}