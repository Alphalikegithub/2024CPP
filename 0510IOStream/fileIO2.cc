#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
using std::string;


void test1(){
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

void test2(){
    ifstream ifs("test.txt");//打开一个名为test.txt的文件
    if(!ifs.good()){
        cerr << "ifstream is not good" << endl;
        return;
    }
    //通过文件流去读取文件
    /*  */
    //对于文件输入流而言，默认以空格为分隔符
    string line;
    while(getline(ifs,line)){
        cout << line << endl;
    }
    ifs.close();
}


void test3(){
    ifstream ifs("test.txt");//打开一个名为test.txt的文件
    if(!ifs.good()){
        cerr << "ifstream is not good" << endl;
        return;
    }
    //通过文件流去读取文件
    /*  */
    //对于文件输入流而言，默认以空格为分隔符
    string line[60];
    size_t idx = 0;
    while(getline(ifs,line[idx])){
        idx ++;
    }

    //打印指定行
    cout << "line[13]:" << line[13] << endl;
    ifs.close();
}

void test4(){
    string filename("test.txt");
    ifstream ifs(filename.c_str());//打开一个名为test.txt的文件
    //ifstream ifs("test.txt");
    if(!ifs.good()){
        cerr << "ifstream is not good" << endl;
        return;
    }
    //通过文件流去读取文件
    /*  */
    //对于文件输入流而言，默认以空格为分隔符
    string line;
    std::vector<string> vec;//创建一个vec对象
    while(getline(ifs,line)){
        vec.push_back(line);
    }
    //打印全部
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i] << endl;
    }
    cout << endl << endl;
    
    //打印指定行
    cout << "vec[11]:" << vec[11] << endl;
    ifs.close();
}
int main(int argc,char **aggv){
    test4();
    return 0;
}