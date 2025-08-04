#include <stdio.h>

int main() {
    printf("Array Fundamentals Demo\n");
    printf("======================\n\n");
    
    // Example array
    int numbers[] = {10, 25, 3, 47, 15};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Array elements: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("Array size: %d elements\n", size);
    printf("First element: %d\n", numbers[0]);
    printf("Last element: %d\n", numbers[size-1]);
    
    return 0;
}
