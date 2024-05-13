#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
using std::string;

void printVectorCapacity(const std::vector<int> &vec){
    cout << "vec.size ="     << vec.size() << endl;
    cout << "vec.capacity =" << vec.capacity() << endl;
}
/* vector底层的扩容原理 */
/* 新内存分配: Vector分配一个新的内存块，该内存块大于当前内存块。新内存块的大小通常由增长因子决定，
    该因子指定每次需要更多空间时vector应该扩展多少。默认增长因子通常为2，这意味着vector在扩展时会将其大小加倍。

    数据迁移: Vector将所有现有元素从旧内存块复制到新内存块中。这确保在扩展过程中不会丢失数据。

    内存释放: 一旦数据迁移完成，旧内存块就会被释放，释放先前占用的内存空间。

    更新内部指针: Vector更新其内部指针（例如_begin和_end）指向新内存块，反映数据的新位置。 
*/
void test(){
    std::vector<int> vec;//没有关注容器中元素的个数
    printVectorCapacity(vec);
    
    cout << endl;
    vec.push_back(1);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(2);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(3);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(4);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(5);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(6);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(7);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(8);
    printVectorCapacity(vec);

    cout << endl;
    vec.push_back(9);
    printVectorCapacity(vec);

}
int main(int argc,char **aggv){
    test();
    return 0;
}