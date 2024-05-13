#include <stdlib.h>  
  
int main() {  
    int *ptr = (int*)malloc(sizeof(int));  
  
    if (ptr == NULL) {  
        printf("Memory not allocated.\n");  
        exit(0);  
    }  
  
    *ptr = 42; // assign a value to the memory location  
  
    printf("Value of *ptr: %d\n", *ptr);  
  
    free(ptr); // this releases the memory  
  
    // after freeing memory, you should not use ptr any more  
    printf("Value of *ptr after free: %d\n", *ptr); // this is undefined behavior  
  
    return 0;  
}