#include <stdio.h>

int main() {
    printf("Pointer Basics Demo\n");
    printf("==================\n\n");
    
    int x = 42;
    int *ptr = &x;
    
    printf("Variable x: value = %d, address = %p\n", x, (void*)&x);
    printf("Pointer ptr: value = %p, address = %p\n", (void*)ptr, (void*)&ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);
    
    printf("\nThis exercise covers:\n");
    printf("- Pointer declaration and initialization\n");
    printf("- Address-of operator (&)\n");
    printf("- Dereference operator (*)\n");
    printf("- Pointer arithmetic\n");
    printf("- Arrays and pointers relationship\n");
    
    return 0;
}
