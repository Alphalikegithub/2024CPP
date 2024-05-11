#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
using std::string;


void test2(){
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
    test2();
    return 0;
}