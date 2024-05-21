#include "TestRedis.h"

int main(int argc, char *argv[])
{
    MyRedis *pRedis = new MyRedis();
    if (!pRedis->connect("127.0.0.1", 6379))
    {
        cout << "connect error!" << endl;
        return 0;
    }
    pRedis->set("name", "Andy");
    cout << "Get the name is " << pRedis->get("name").c_str() << endl;
    delete pRedis;
    return 0;
}