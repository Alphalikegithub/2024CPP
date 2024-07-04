通过组合（composition）来塑造 `has-a` 或 `use-a` 关系，是一种面向对象编程的设计原则。这种方法通过在一个类中包含另一个类的实例来实现，而不是通过继承。这样可以提高代码的可维护性、可重用性和灵活性。

### `has-a` 关系

`has-a` 关系表示一个类拥有另一个类的实例。比如，一个 `Car` 类可以有一个 `Engine` 类的实例，这表示车有一个引擎。

### `use-a` 关系

`use-a` 关系表示一个类使用另一个类的实例。比如，一个 `Driver` 类可以使用一个 `Car` 类的实例，这表示驾驶员使用一辆车。

### 示例代码

以下是一个通过组合来实现 `has-a` 和 `use-a` 关系的示例代码：

#### `has-a` 关系示例

```cpp
#include <iostream>

// Engine 类
class Engine {
public:
    void start() const {
        std::cout << "Engine started" << std::endl;
    }
};

// Car 类，拥有一个 Engine 实例，表示 has-a 关系
class Car {
public:
    Car() : engine_() {}

    void start() const {
        engine_.start();
    }

private:
    Engine engine_;  // Car has an Engine
};

int main() {
    Car car;
    car.start();  // 输出 "Engine started"
    return 0;
}
```

#### `use-a` 关系示例

```cpp
#include <iostream>

// Car 类
class Car {
public:
    void drive() const {
        std::cout << "Car is being driven" << std::endl;
    }
};

// Driver 类，使用一个 Car 实例，表示 use-a 关系
class Driver {
public:
    void driveCar(const Car& car) const {
        car.drive();
    }
};

int main() {
    Car car;
    Driver driver;
    driver.driveCar(car);  // 输出 "Car is being driven"
    return 0;
}
```

### 代码解释

1. **`Engine` 类和 `Car` 类**：
   - `Engine` 类包含一个 `start` 方法，用于启动引擎。
   - `Car` 类包含一个 `Engine` 类的实例，通过 `engine_` 成员变量表示 `has-a` 关系。`Car` 类的 `start` 方法调用 `engine_` 的 `start` 方法。

2. **`Car` 类和 `Driver` 类**：
   - `Car` 类包含一个 `drive` 方法，用于表示车的驾驶行为。
   - `Driver` 类通过 `driveCar` 方法使用一个 `Car` 类的实例，表示 `use-a` 关系。

### 组合的优势

1. **灵活性**：
   - 通过组合，可以在运行时改变被组合对象的类型和数量，而继承是在编译时确定的。

2. **低耦合性**：
   - 组合减少了类之间的耦合度，使代码更容易维护和扩展。

3. **重用性**：
   - 通过组合，可以重用现有类的功能，而不需要通过继承来扩展类。

4. **替代继承**：
   - 组合可以替代一些情况下的继承，避免了多重继承的复杂性和潜在问题。

总之，通过组合来塑造 `has-a` 或 `use-a` 关系，是一种强大且灵活的面向对象设计方法，可以提升代码的可维护性和可重用性。