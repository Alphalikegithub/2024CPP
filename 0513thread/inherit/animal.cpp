#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Animal
{
private:
    /* data */
public:
    // 通用属性
    
    // 通用方法
    virtual void eat() = 0;  // 虚函数：需要在派生类中实现
    virtual void sleep() = 0;  // 虚函数：需要在派生类中实现
public:
    std::string name;
    int age;
};

class Dog :public Animal
{
private:
    // 特有方法
    void bark(){
        std::cout << "汪汪汪" << std::endl;
    }

    // 特有属性
    std::string breed;
private:
    void eat() override{
        std::cout << "狗在吃骨头" << std::endl;
    }
    void sleep() override{
        std::cout << "狗趴在地上睡觉" << std::endl;
    }
};

class Cat :public Animal
{
public:
  // 特有属性
  bool hasFur;

  // 特有方法
  void meow() {
    std::cout << "喵喵喵" << std::endl;
  }
private:
    void eat() override{
        std::cout << "猫在吃鱼" << std::endl;
    }
    void sleep() override{
        std::cout << "猫在蜷缩着睡觉" << std::endl;

    }
};

int main(){
    Animal *pAnimal;
    pAnimal = new Cat();
    pAnimal->eat();  // 输出：猫在吃鱼
    pAnimal->sleep(); // 输出：猫在蜷缩着睡觉

    pAnimal = new Dog();
    pAnimal->eat();  // 输出：狗在吃骨头
    pAnimal->sleep(); // 输出：狗趴在地上睡觉
    
}


