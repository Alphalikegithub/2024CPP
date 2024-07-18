#include <iostream>  
  
void QuickSort(int array[], int L, int R) {  
    if (L >= R) {  
        return;  
    }  
    int left = L;  
    int right = R;  
    int pivot = array[left];  
    while (left < right) {  
        while (left < right && array[right] >= pivot) {  
            right--;  
        }  
        if (left < right) {  
            array[left] = array[right];  
        }  
  
        while (left < right && array[left] <= pivot) {  
            left++;  
        }  
        if (left < right) {  
            array[right] = array[left];  
        }  
    }  
    array[left] = pivot;  
  
    QuickSort(array, L, left - 1);  
    QuickSort(array, left + 1, R);  
}  
  
/* int main() {  
    int array[] = {7, 5, 4, 2, 3, 4, 1, 3, 8, 9, 6};  
    int *p = array;  
    QuickSort(p, 0, 10);  
    for (int i = 0; i < 11; i++) {  
        std::cout << array[i] << " ";  
    }  
    std::cout << std::endl;  
  
    return 0;  
} */

int main() {  
    int array[] = {7, 5, 4, 2, 3, 4, 1, 3, 8, 9, 6};  
    int n = sizeof(array) / sizeof(array[0]);  
    QuickSort(array, 0, n - 1); // 调用QuickSort，注意R是n-1  
  
    for (int i = 0; i < n; i++) {  
        std::cout << array[i] << " ";  
    }  
    std::cout << std::endl;  
  
    return 0;  
}