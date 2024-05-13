#include <iostream>
#include <fstream>
#include <vector>
#include "fileIO3.h"

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
using std::string;
using std::ofstream;
using std::fstream;


void test1(){
    //文件输入输出流
    /* 对于文件的输入输出流而言，当文件不存在的时候，就打开失败 */
    fstream fs("testfstream.txt");
    if(!fs.good()){
        cerr << "fstream is not good!" << endl;
        return;
    }
    
    cout << endl;
    

    fs.close();
}





int main(int argc,char **aggv){
    test1();
    return 0;
}