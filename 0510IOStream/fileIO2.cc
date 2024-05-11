#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
using std::string;
using std::ofstream;


void test1(){
    //通过文件流去读取文件
    ifstream ifs("test.txt");//打开一个名为test.txt的文件
    if(!ifs.good()){
        cerr << "ifstream is not good" << endl;
        return;
    }
    //写文件
    //对于文件输出流而言，当文件不存在的时候就创建文件
    /* 对于文件输出流而言，当文件不存在的时候就创建文件
       当文件存在且其中有内容，会覆盖该文件（清空文件）
     */
    ofstream ofs("testwrite.txt");
    if(!ofs.good()){
        cerr << "ofstream is not good!" << endl;
        ifs.close();//防止ofs意外，不能及时关闭ifs
        return;
    }

    
    /*  */
    //对于文件输入流而言，默认以空格为分隔符
    string line;
    while(getline(ifs,line)){
        ofs << line << endl;
    }
    ifs.close();
    ofs.close();
}

void test2(){

    //对于文件输出流而言，当文件不存在的时候就创建文件
    /* 对于文件输出流而言，当文件不存在的时候就创建文件
       当文件存在且其中有内容，会覆盖该文件（清空文件）
     */
    ofstream ofs("testwrite.txt");
    if(!ofs.good()){
        cerr << "ofstream is not good!" << endl;
        return;
    }

    ofs.close();
}



int main(int argc,char **aggv){
    test1();
    return 0;
}