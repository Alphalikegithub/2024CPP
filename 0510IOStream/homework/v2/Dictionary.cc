#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::string;
using std::vector;
using std::istringstream;
using std::ostringstream;
using std::ifstream;
using std::ofstream;

struct Record{
    Record(const string &word,int frequency)
    :_word(word)
    ,_frequency(frequency)
    {

    }
    string _word;
    int _frequency;
};

class Dictionary
{
private:
    vector<Record> _dict;
public:
    void read(const string &filename);//读取The_Holy_Bible.txt中的内容
    //细节处理：判断单词是否规范，如果合格就放在vector中
    void store(const string &filename);//遍历vector,用ofs写到filename文件中

    
    string dealWord(const string &word);
    void insert(const string &word);
};

//将单词与词频按照顺序存储起来


/* 
一行一行的去读The_Holy_Bible.txt这个文件(文件输入流istringstream默认是以空格为分隔符，可以一个单词一个单词的读出来)
用vector容器去存储后 _dict++
最后遍历vector,将解析后的结果存储到另外一个文件
 */
void Dictionary::read(const string &filename){
    //打开文件
    ifstream ifs(filename.c_str());
    if(!ifs.good()){
        cerr << "open" << filename << "error!" <<endl;
        return ;
    }
    //读filename这个文件,然后对每一个单词做处理
    //为了避免一个单词一个单词的读效率太低，可以逐行读取

    
    string line;
    while(getline(ifs,line)){
        //读取一行之后的数据存放到istringstream(字符串IO)
        istringstream iss(line);

        string word;
        while (iss >> word)//串IO是在内存中进行读写的
        {
            /* code */
            //word一定是最终要保存的单词吗(判断是否合规)
            string newWord = dealWord(word);
            insert(newWord);//将满足条件的单词存放到vector中
        }
        
    }


    ifs.close();
}

void Dictionary::store(const string &filename){
    ofstream ofs(filename.c_str());
    for (size_t i = 0; i != _dict.size(); ++i)
    {
        ofs << _dict[i]._word << "    " << _dict[i]._frequency << endl;
    }
    ofs.close();
}

string Dictionary::dealWord(const string &word)
{
    for (size_t i = 0; i < word.size(); i++)
    {
        /* if(word[i] >= 'a' && word[i] <= 'z' || (word[i] >= 'A' && word[i] <= 'Z')){

        } */
        //检查给定字符是否为字母字符
        if(!isalpha(word[i])){
            return string();//返回一个空串
        }
    }
    
    return word;
}

void Dictionary::insert(const string &word)
{
    if(word == string()){
        return;
    }
    size_t i = 0;
    for(i;i != _dict.size();++i){
        if(word == _dict[i]._word){
            ++ _dict[i]._frequency;
            break;
        }
    }

    if(i == _dict.size()){
        _dict.push_back(Record(word,1));
    }
}

void test(){
    
}

int main(int argc,char **argv){
    Dictionary dictonary;
    cout << "start reading..." << endl;
    dictonary.read("The_Holy_Bible.txt");
    cout << "finished!" << endl;
    dictonary.store("yyds.dat");
    return 0;
}

