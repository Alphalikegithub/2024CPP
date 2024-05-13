#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::cin;

class Base
{
    public:
    Base(const char *pbase)
    :_pbase(new char[strlen(pbase) + 1]())
    {
        cout << "Base(const char *)" << endl;
        strcpy(_pbase,pbase);
    }

    virtual void print() const
    {
        if(_pbase)
        {
            cout << "Base::_pbase = " << _pbase << endl;
        }
    }
    ~Base()
    {
        cout << "~Base()" << endl;
        if(_pbase)
        {
            delete [] _pbase;
            _pbase = nullptr;
        }
    }
    private:
    char *_pbase;
};

class Derived
:public Base
{
    public:
    Derived(const char *pbase,const char *pderived)
    :Base(pbase)
    ,_pderived(new char[strlen(pderived) + 1]())
    {
        cout << "Derived(const char *,const char *)" << endl;
        strcpy(_pderived,pderived);
    }

    void print() const
    {
        if(_pderived)
        {
            cout << "Base::_pderived = " << _pderived << endl;
        }
    }
    ~Derived()
    {
        cout << "~Derived()" << endl;
        if(_pderived)
        {
            delete [] _pderived;
            _pderived = nullptr;
        }
    }
    private:
    char *_pderived;
};

void test()
{
    Base *pbase = new Derived("hello","world");
    pbase->print();

    delete pbase;
    pbase = nullptr;
}

int main(int argc,char **argv)
{

    test();
    return 0;
}