#include <stdio.h>
#include <stdlib.h>    
  
    
int main() {    
    int *ptr = (int*)malloc(sizeof(int));    
    if (ptr == NULL) {   
        printf("Memory not allocated.\n");    
        exit(0);    
    }    
    
    *ptr = 42; // assign a value to the allocated memory location    
    
    printf("Value of *ptr: %d\n", *ptr);    
    
    free(ptr); // this releases the memory    
    ptr = NULL; // set the pointer to NULL immediately after freeing  
  
    // Checking if ptr is NULL before dereferencing it  
    if (ptr == NULL) {  
        printf("Pointer is NULL, cannot access *ptr.\n");  
    } else {  
        // This block will never execute because ptr is set to NULL above  
        printf("Value of *ptr after free: %d\n", *ptr);  
    }  
    
    return 0;    
}