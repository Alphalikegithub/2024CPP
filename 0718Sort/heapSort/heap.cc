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

    if(max != i){
        swap(tree,max,i);
        heapify(tree,n,max);
    }
}
int main(){
    int tree[] = {4,10,3,5,1,2};
    int length = sizeof(tree) / tree[0];
     heapify(tree,length,0);

     for(int  i = 0;i < length ;i++){
        std::cout << tree[i] << " ";
     }
     std::cout << std::endl;
     return 0;
}