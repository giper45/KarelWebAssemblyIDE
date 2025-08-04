#include <stdio.h>

// TODO: Create a function that swaps two integers using pointers
// Function name: swap
// Parameters: two integer pointers
// Returns: void

// TODO: Create a function that finds the maximum element in an array using pointers
// Function name: find_max_ptr
// Parameters: pointer to array, size
// Returns: pointer to the maximum element

int main() {
    // TODO: Declare variables and pointers
    int num1 = 10, num2 = 20;
    int *ptr1, *ptr2;
    
    // TODO: Initialize pointers to point to the variables
    
    // TODO: Print addresses and values
    // - Print address of num1 and num2
    // - Print values of ptr1 and ptr2 (addresses they store)
    // - Print values pointed to by ptr1 and ptr2
    
    // TODO: Modify values through pointers
    // Change num1 to 100 using ptr1
    // Change num2 to 200 using ptr2
    
    // TODO: Test the swap function
    printf("Before swap: num1=%d, num2=%d\n", num1, num2);
    // Call swap function
    printf("After swap: num1=%d, num2=%d\n", num1, num2);
    
    // TODO: Work with arrays and pointers
    int arr[] = {5, 2, 8, 1, 9, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    // TODO: Use pointer arithmetic to traverse the array
    // Print all elements using pointer arithmetic
    
    // TODO: Find maximum element using the pointer function
    
    // TODO: Demonstrate the relationship between arrays and pointers
    // Show that arr[i] is equivalent to *(arr + i)
    
    // TODO: Show pointer arithmetic
    // - What happens when you add 1 to an int pointer?
    // - What's the difference between ptr and ptr+1?
    
    return 0;
}

// TODO: Implement the swap function here

// TODO: Implement the find_max_ptr function here
