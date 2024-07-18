#include <iostream>

#if 1
//快速排序（low左边小于pivot，high右边大于pivot）
int Partition(int a[],int low,int high){
    int pivot = a[low];//pivot : 中心，支点
    while(low < high){
        while(low < high && a[high] >= pivot){
            high --;
        }
        a[low] = a[high];
        while(low < high && a[low] <= pivot){
            low ++;
        }
        a[high] = a[low];
    }
    a[low] = pivot;//最后low和high会相遇，我的理解是a[low]和a[right]指向同一片空间---a[high] = pivot;也是正确的
    return low;
}
#endif

#if 0
int Partition(int a[], int low, int high) {  
    int pivot = a[low];  
    int i = low - 1; // i 指向小于pivot的最后一个元素的右边  
    for (int j = low; j < high; j++) {  
        if (a[j] < pivot) {  
            i++;  
            // 交换 a[i] 和 a[j]  
            int temp = a[i];  
            a[i] = a[j];  
            a[j] = temp;  
        }  
    }  
    // 将pivot放到正确的位置  
    int temp = a[i + 1];  
    a[i + 1] = a[high];  
    a[high] = temp;  
    return i + 1;  
}

# endif


void QuickSort(int a[],int low, int high){
    if(low  < high){
        int pivotPos = Partition(a,low,high);//假设总共有八个元素(下标0~7)，此时 pivot的下标为3
        QuickSort(a,low,pivotPos - 1);//左半部分(0,2)
        QuickSort(a,pivotPos + 1,high);//右半部分(4,7)
    }
}


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