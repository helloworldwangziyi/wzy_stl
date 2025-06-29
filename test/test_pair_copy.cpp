#include <iostream>
#include "../src/util.hpp"  // 包含pair定义的头文件

// 用于跟踪构造函数调用的自定义类
class Tracker {
public:
    int value;
    static int copy_count;
    static int move_count;
    
    Tracker(int v = 0) : value(v) {
        std::cout << "默认/值构造 Tracker(" << value << ")" << std::endl;
    }
    
    Tracker(const Tracker& other) : value(other.value) {
        copy_count++;
        std::cout << "拷贝构造 Tracker(" << value << ") #" << copy_count << std::endl;
    }
    
    Tracker(Tracker&& other) noexcept : value(other.value) {
        move_count++;
        other.value = -1;
        std::cout << "移动构造 Tracker(" << value << ") #" << move_count << std::endl;
    }
    
    ~Tracker() {
        std::cout << "析构 Tracker(" << value << ")" << std::endl;
    }
    
    // 禁用赋值运算符以确保只测试构造函数
    Tracker& operator=(const Tracker&) = delete;
    Tracker& operator=(Tracker&&) = delete;
};

int Tracker::copy_count = 0;
int Tracker::move_count = 0;

// 不可隐式转换为Tracker的类
class NonConvertible {
public:
    int value;
    
    explicit NonConvertible(int v = 0) : value(v) {
        std::cout << "构造 NonConvertible(" << value << ")" << std::endl;
    }
    
    NonConvertible(const NonConvertible& other) : value(other.value) {
        std::cout << "拷贝构造 NonConvertible(" << value << ")" << std::endl;
    }
};

// 测试隐式转换构造函数
void test_implicit_conversion() {
    std::cout << "\n=== 测试隐式转换构造函数 ===\n";
    
    wzy_stl::pair<Tracker, Tracker> p1(10, 20);
    std::cout << "p1创建完成: (" << p1.first.value << ", " << p1.second.value << ")\n";
    
    // 使用隐式转换的拷贝构造
    wzy_stl::pair<Tracker, Tracker> p2 = p1;
    std::cout << "p2创建完成: (" << p2.first.value << ", " << p2.second.value << ")\n";
    
    // 使用不同类型的隐式转换（如果支持）
    try {
        wzy_stl::pair<int, double> p3(1, 2);
        wzy_stl::pair<Tracker, Tracker> p4 = p3;  // 尝试从int,double转换到Tracker,Tracker
        std::cout << "p4创建完成: (" << p4.first.value << ", " << p4.second.value << ")\n";
    } catch (...) {
        std::cout << "从int,double到Tracker,Tracker的转换失败\n";
    }
}

// 测试显式构造函数
void test_explicit_conversion() {
    std::cout << "\n=== 测试显式转换构造函数 ===\n";
    
    // 使用NonConvertible测试显式构造
    wzy_stl::pair<NonConvertible, NonConvertible> p5(NonConvertible(30), NonConvertible(40));
    std::cout << "p5创建完成: (" << p5.first.value << ", " << p5.second.value << ")\n";
    
    // 显式调用拷贝构造函数
    wzy_stl::pair<NonConvertible, NonConvertible> p6(p5);
    std::cout << "p6创建完成: (" << p6.first.value << ", " << p6.second.value << ")\n";
    
    // 下面这行如果取消注释，应该会编译失败，因为需要显式构造
    wzy_stl::pair<int, int> p18(3, 4);
    // wzy_stl::pair<NonConvertible, NonConvertible> p7 = p18;
    wzy_stl::pair<NonConvertible, NonConvertible> p7;
    // p7 = p18; 编译失败 没有
    // 使用不同类型的显式构造
    try {
        wzy_stl::pair<int, int> p8(3, 4);
        // 显式构造
        wzy_stl::pair<NonConvertible, NonConvertible> p9(p8);
        std::cout << "p9创建完成: (" << p9.first.value << ", " << p9.second.value << ")\n";
    } catch (...) {
        std::cout << "从int,int到NonConvertible,NonConvertible的显式转换失败\n";
    }
}

// 添加一个volatile变量防止优化
volatile bool prevent_optimization = true;

int main() {
    // 在全局作用域显式实例化模板
    // 这会强制编译器生成这些特定类型的模板实例
    
    std::cout << "开始测试pair拷贝构造函数...\n";
    
    if (prevent_optimization) {
        test_implicit_conversion();
        test_explicit_conversion();
    }
    NonConvertible n = NonConvertible(1);
    
    std::cout << "\n总计拷贝构造次数: " << Tracker::copy_count << std::endl;
    std::cout << "总计移动构造次数: " << Tracker::move_count << std::endl;
    
    std::cout << "\n测试完成!\n";
    return 0;
}