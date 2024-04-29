#include <iostream>
#include <string>

using namespace std;

class Animal {
protected:
  string name;
  int age;

public:
  Animal(string name, int age) : name(name), age(age) {}
  virtual void speak() = 0;  // 纯虚函数，子类必须重写
  virtual void move() = 0;  // 纯虚函数，子类必须重写

  string getName() { return name; }
  int getAge() { return age; }

  virtual ~Animal() {}  // 虚析构函数
};

class Bird : public Animal {
public:
  Bird(string name, int age) : Animal(name, age) {}
  void speak() { cout << "啾啾！" << endl; }
  void move() { cout << "飞翔！" << endl; }
};

class Cat : public Animal {
public:
  Cat(string name, int age) : Animal(name, age) {}
  void speak() { cout << "喵喵！" << endl; }
  void move() { cout << "爬行！" << endl; }
};

int main() {
  Animal* animal1 = new Bird("小鸟", 1);
  animal1->speak();
  animal1->move();

  Animal* animal2 = new Cat("小花猫", 2);
  animal2->speak();
  animal2->move();
  
  Animal* cat1 = new Cat("大狸花猫",3);
  cat1->speak();

  delete animal1;
  delete animal2;

  return 0;
}
