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
    //业务逻辑
    /* 通用在控制台键盘输入，把信息输入到testfstream.txt文件中 */
    int number = 0;
    for (size_t i = 0; i != 5; ++i)
    {
        cin >> number;
        fs << number << " ";
    }
    printstatus(fs);

    /* 
    tellg||tellp     seekp||seekg
    p = put;g = get
    p在输出的时候使用(put写入)   （get读取）
     */
    size_t len = fs.tellp();
    cout << "len = " << len << endl;//指针偏移的长度
    //fs.seekp(0);//将指针偏移到0的位置
    //将文件指针偏移到相对位置
    fs.seekp(-10,std::ios::end);//相对于文件指针尾部向前偏移10个位置
    cout << "指针偏移后：";
    len = fs.tellp();
    cout << "len = " << len << endl;

    cout << "下面是testfstream.txt中的内容:" << endl;
    /* 用fs读文件，并输出到控制台 */
    for (size_t i = 0; i != 5; ++i)
    {
        //将文件指针指向文件的头部
        //printstatus(fs);
        fs >> number ;
        cout << number << " ";
    }
    cout << endl;
    

    fs.close();
}

void printstatus(std::fstream &fs)
{
    cout << "打印文件流的状态:" << endl;
    cout << "fs.failbit = " << fs.fail() << endl
         << "fs.eofbit = " << fs.eof() << endl
         << "fs.goodbit = " << fs.good() << endl;
}
void test2()
{

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