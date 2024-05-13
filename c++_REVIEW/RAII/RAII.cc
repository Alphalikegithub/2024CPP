#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;
template <typename T>
class RAII
{
public:
    RAII(T *data)
    :_data(data)
    {
        cout << "RAII(T *)" << endl;
    }
    ~RAII()
    {
        if(_data)
        {
            delete _data;
            _data = nullptr;
        }
        cout << "~RAII()" << endl;
    }
    //提供若干访问资源的方法
    T *operator->()
    {
        return _data;
    }
    T &operator*()
    {
        return &_data;
    }
    T *get()
    {
       return _data; 
    }
    void reset(T *data)
    {
        if(_data)
        {
            delete _data;
            _data = nullptr;
        }
        _data = data;
    }
    //不允许复制或者赋值
    RAII(const RAII &rhs) = delete;
    RAII &operator = (const RAII &rhs) = delete;
private:
    T *_data;
};
int main(int argc , char **argv)
{
    RAII<int> raii1(new int(10));//栈对象的生命周期
    return 0;
}