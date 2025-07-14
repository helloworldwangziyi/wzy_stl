#include <iostream>
#include "../src/algobase.hpp"

struct A
{
    int a;
};

int main()
{
    int a = 1, b = 2;
    std::cout << wzy_stl::max(a, b) << std::endl;

    A a1, a2;
    a1.a = 1;
    a2.a = 2;
    std::cout << wzy_stl::max(a1, a2, [](const A& lhs, const A& rhs) {return lhs.a < rhs.a;}).a << std::endl;

    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5];
    wzy_stl::unchecked_copy<int, int>(arr1, arr1 + 5, arr2);
    for(int i = 0; i < 5; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    // 测试 unchecked_copy_backward 特化版本（平凡可复制类型）
    std::cout << "\n=== 测试 unchecked_copy_backward 特化版本 ===" << std::endl;
    
    // 测试1：基本反向复制
    int source1[5] = {1, 2, 3, 4, 5};
    int dest1[5] = {0, 0, 0, 0, 0};
    
    std::cout << "测试1 - 基本反向复制:" << std::endl;
    std::cout << "源数组: ";
    for(int i = 0; i < 5; i++) std::cout << source1[i] << " ";
    std::cout << std::endl;
    
    std::cout << "目标数组(复制前): ";
    for(int i = 0; i < 5; i++) std::cout << dest1[i] << " ";
    std::cout << std::endl;
    
    wzy_stl::unchecked_copy_backward<int, int>(source1, source1 + 5, dest1 + 5);
    
    std::cout << "目标数组(复制后): ";
    for(int i = 0; i < 5; i++) std::cout << dest1[i] << " ";
    std::cout << std::endl;
    
    // 测试2：重叠区域复制
    int arr_overlap[7] = {1, 2, 3, 4, 5, 0, 0};
    std::cout << "\n测试2 - 重叠区域复制:" << std::endl;
    std::cout << "原始数组: ";
    for(int i = 0; i < 7; i++) std::cout << arr_overlap[i] << " ";
    std::cout << std::endl;
    
    // 把 [1,2,3] 复制到 [4,5,0] 的位置
    wzy_stl::unchecked_copy_backward<int, int>(arr_overlap, arr_overlap + 3, arr_overlap + 6);
    
    std::cout << "复制后数组: ";
    for(int i = 0; i < 7; i++) std::cout << arr_overlap[i] << " ";
    std::cout << std::endl;
    
    // 测试3：double类型测试
    double source_double[4] = {1.1, 2.2, 3.3, 4.4};
    double dest_double[4] = {0.0, 0.0, 0.0, 0.0};
    
    std::cout << "\n测试3 - double类型测试:" << std::endl;
    std::cout << "源数组: ";
    for(int i = 0; i < 4; i++) std::cout << source_double[i] << " ";
    std::cout << std::endl;
    
    wzy_stl::unchecked_copy_backward<double, double>(source_double, source_double + 4, dest_double + 4);
    
    std::cout << "目标数组: ";
    for(int i = 0; i < 4; i++) std::cout << dest_double[i] << " ";
    std::cout << std::endl;
    
    // 测试4：char类型测试
    char source_char[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char dest_char[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
    
    std::cout << "\n测试4 - char类型测试:" << std::endl;
    std::cout << "源字符串: " << source_char << std::endl;
    
    wzy_stl::unchecked_copy_backward<char, char>(source_char, source_char + 5, dest_char + 5);
    
    std::cout << "目标字符串: " << dest_char << std::endl;
    
    // 测试5：空范围测试
    int empty_source[3] = {1, 2, 3};
    int empty_dest[3] = {0, 0, 0};
    
    std::cout << "\n测试5 - 空范围测试:" << std::endl;
    std::cout << "目标数组(复制前): ";
    for(int i = 0; i < 3; i++) std::cout << empty_dest[i] << " ";
    std::cout << std::endl;
    
    wzy_stl::unchecked_copy_backward<int, int>(empty_source, empty_source, empty_dest + 3);
    
    std::cout << "目标数组(复制后): ";
    for(int i = 0; i < 3; i++) std::cout << empty_dest[i] << " ";
    std::cout << std::endl;
    
    // 测试6：验证返回值
    int test_source[3] = {10, 20, 30};
    int test_dest[3] = {0, 0, 0};
    
    std::cout << "\n测试6 - 验证返回值:" << std::endl;
    int* result = wzy_stl::unchecked_copy_backward<int, int>(test_source, test_source + 3, test_dest + 3);
    
    std::cout << "返回值指向的位置: " << (result - test_dest) << std::endl;
    std::cout << "目标数组: ";
    for(int i = 0; i < 3; i++) std::cout << test_dest[i] << " ";
    std::cout << std::endl;
    
    return 0;
}