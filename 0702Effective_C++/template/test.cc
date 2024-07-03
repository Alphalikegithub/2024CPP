#include <algorithm>
#include <iostream>

// 定义一个用于打印数组内容的模板函数
template <typename T>
void printArray(const T* array, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// 定义一个用于排序数组的模板函数
template <typename T>
void sortArray(T* array, int size) {
    std::sort(array, array + size);
}

int main() {
    int arr1[] = {3, 1, 4, 1, 5};
    sortArray(arr1, 5);
    printArray(arr1, 5); // 打印排序后的 int 数组

    double arr2[] = {3.5, 1.2, 4.6, 1.1, 5.3};
    sortArray(arr2, 5);
    printArray(arr2, 5); // 打印排序后的 double 数组

    return 0;
}
