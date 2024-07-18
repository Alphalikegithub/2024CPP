#include <iostream>

void swap(int arr[],int i,int j ){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//n代表一棵树中有几个结点
void heapify(int tree[],int n,int i){
    if(i >= n){
        return;
    }
    int c1 = 2 * i + 1;
    int c2 = 2 * i + 2;
    //在三个结点里面找出最大值（一个parent和两个child）
    int max = i;
    if(c1 < n && tree[c1] > tree[max]){
        max = c1;
    }
    if(c2 < n && tree[c2] > tree[max]){
        max = c2;
    }
    //说明i 结点还有孩子比i大
    if(max != i){
        swap(tree,max,i);
        heapify(tree,n,max);
    }
}
//建堆的过程
void build_heap(int tree[],int n){
    int last_node = n - 1;
    int parent  = (last_node - 1) / 2;
    for(int i = parent;i >= 0;i--){
        heapify(tree,n,i);
    }
}
//一个大根堆中，根结点的值大于子节点
//排序的过程
void heap_sort(int tree[],int n){
    build_heap(tree,n);
    for(int i = n - 1; i >= 0; i--){
        swap(tree,i,0);
        heapify(tree,i,0);//i代表的是当前这个数的结点个数
    }
}
int main(){

    int tree[] = {2,5,3,1,10,4};
    int length = sizeof(tree) / sizeof(tree[0]);
    
    //heapify(tree,length,0);
    //build_heap(tree,length);
    heap_sort(tree,length);

    for(int  i = 0;i < length ;i++){
        std::cout << tree[i] << " ";
    }
    for(int  j = 0;j < 100;j++){
        //大根堆和小根堆的创建过程 孩子结点是父亲节点的二倍 
    }
    std::cout << std::endl;
    return 0;
}